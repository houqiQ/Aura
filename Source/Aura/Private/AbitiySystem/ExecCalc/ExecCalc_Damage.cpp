// Fill out your copyright notice in the Description page of Project Settings.


#include "AbitiySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "AuraAbilityTypes.h"
#include "AuraGameplayTags.h"
#include "AbitiySystem/AuraAbilitySystemLibrary.h"
#include "AbitiySystem/AuraAttributeSet.h"
#include "AbitiySystem/Data/CharaterClassInfo.h"
#include "Interaction/CombatInterface.h"

//这个只是在这个类里面用 不用反射
struct AuraDamageStatics
{
	//宏  DECLARE_ATTRIBUTE_CAPTUREDEF 是 GAS 里的一个“声明宏”，用于告诉系统：“我要捕获某个属性”。它需要配合 DEFINE_ATTRIBUTE_CAPTUREDEF 一起使用，一个负责“声明变量”，另一个负责“给变量赋值”
	
	//护甲
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	//格挡率
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	//护甲穿透
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	//暴击率
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	//暴击伤害
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);
	//暴击抗性
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance);
	//火焰抗性
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance);
	//闪电抗性
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance);
	//奥术抗性
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArcaneResistance);
	//物理抗性
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalResistance);
	
	
	//使用一个T映射 把玩法标签映射到玩法属性捕获定义上
	TMap<FGameplayTag,FGameplayEffectAttributeCaptureDefinition>TagSToCaptureDefs;
	AuraDamageStatics()
	{
		//创建并定义了一个名为Armor的属性捕获定义
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,Armor,Target,false);
		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,BlockChance,Target,false);
		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,ArmorPenetration,	Source,false);
		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,CriticalHitChance,Source,false);
		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,CriticalHitDamage,Source,false);
		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,CriticalHitResistance,Target,false);
		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,FireResistance,Target,false);
		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,LightningResistance,Target,false);
		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,ArcaneResistance,Target,false);
		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,PhysicalResistance,Target,false);
		
		const FAuraGameplayTags Tags=FAuraGameplayTags::Get();
		TagSToCaptureDefs.Add(Tags.Attributes_Secondary_Armor,ArmorDef);
		TagSToCaptureDefs.Add(Tags.Attributes_Secondary_BlockChance,BlockChanceDef);
		TagSToCaptureDefs.Add(Tags.Attributes_Secondary_ArmorPenetration,ArmorPenetrationDef);
		TagSToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalHitChance,CriticalHitChanceDef);
		TagSToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalHitResistance,CriticalHitResistanceDef);
		TagSToCaptureDefs.Add(Tags.Attributes_Resistance_Fire,FireResistanceDef);
		TagSToCaptureDefs.Add(Tags.Attributes_Resistance_Lightning,LightningResistanceDef);
		TagSToCaptureDefs.Add(Tags.Attributes_Resistance_Arcane,ArcaneResistanceDef);
		TagSToCaptureDefs.Add(Tags.Attributes_Resistance_Physical,PhysicalResistanceDef);
		UE_LOG(LogTemp, Warning, TEXT("AuraDamageStatics 构造函数被调用了！"));
		
	}
};
//只创造一次
static const AuraDamageStatics& DamageStatics()
{
	static AuraDamageStatics DStatics;
	return DStatics;
}
UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
	
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanceDef);
	
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitDamageDef);
	
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitResistanceDef);
	
	RelevantAttributesToCapture.Add(DamageStatics().FireResistanceDef);
	
	RelevantAttributesToCapture.Add(DamageStatics().LightningResistanceDef);
	
	RelevantAttributesToCapture.Add(DamageStatics().ArcaneResistanceDef);
	
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalResistanceDef);
	
	
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent*SourceASC=ExecutionParams.GetSourceAbilitySystemComponent();
	
	UAbilitySystemComponent*TargetASC=ExecutionParams.GetTargetAbilitySystemComponent();
	
	AActor*SourceAvActor=SourceASC?SourceASC->GetAvatarActor():nullptr;
	
	AActor*TargetAvActor=TargetASC?TargetASC->GetAvatarActor():nullptr;
	
	FGameplayEffectSpec Spec=ExecutionParams.GetOwningSpec();
	ICombatInterface *SourceCombatInterface=Cast<ICombatInterface>(SourceAvActor);
	ICombatInterface *TargetCombatInterface=Cast<ICombatInterface>(TargetAvActor);
	
	
	//从源数据和目标数据中收集标签
	const FGameplayTagContainer*SourceTags=Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer*TargetTags=Spec.CapturedTargetTags.GetAggregatedTags();
	
	//捕获属性并获取它的数值大小
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags=SourceTags;
	EvaluateParameters.TargetTags=TargetTags;
	
	//或者上下文
	FGameplayEffectContextHandle EffectContextHandle=Spec.GetContext();
	//static_casts  是C++的
	FAuraGameplayEffectContext*AuraContext=static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get());
	
	
	
	
	// 伤害由调用者的幅度设定
	
	
	float Damage=0;
	
	
	for (auto Pair:FAuraGameplayTags::Get().DamageTypesToResistance)
	{
		//伤害标签
		const FGameplayTag DamageTag=Pair.Key;
		//抗性标签
		const FGameplayTag ResistanceTag=Pair.Value;
		AuraDamageStatics  asd=DamageStatics();
		checkf(DamageStatics().TagSToCaptureDefs.Contains(ResistanceTag),TEXT("void UExecCalc_Damage::Execute_Implementation中 没有这个Tag [%s]"),*ResistanceTag.ToString());
		
		
		const FGameplayEffectAttributeCaptureDefinition CaptureDef=DamageStatics().TagSToCaptureDefs[ResistanceTag];
		
		//           获取调用者设定的幅度 这个是技能上拿数据
		float DamageTypeValue=Spec.GetSetByCallerMagnitude(Pair.Key,false);
		
		float ResistancePenetration=0;
		//这个是角色上拿数据
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDef,EvaluateParameters,ResistancePenetration);
		ResistancePenetration=FMath::Clamp(ResistancePenetration,0.f,100.f);
		
		
		//抗性是 0~100 的百分比，这里要除以 100；写成 (1 - 抗性) 的话抗性>1 就会把伤害变成负数
		Damage+=DamageTypeValue*(100-ResistancePenetration)/100;
	}
	
	//护甲
	float TargetArmor=0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef,EvaluateParameters,TargetArmor);
	TargetArmor=FMath::Max<float>(0,TargetArmor);
	
	
	//护甲穿透忽略目标护甲的百分比
	float SourceArmorPenetration=0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef,EvaluateParameters,SourceArmorPenetration);
	SourceArmorPenetration=FMath::Max<float>(0,SourceArmorPenetration);
	
	//获取伤害系数
	UCharaterClassInfo * CharaterClassInfo=UAuraAbilitySystemLibrary::GetCharaterClassInfo(SourceAvActor);
	//找到曲线后，要指定这个曲线的行名                                                        需要一个上下蚊子串 可以传入一个空的
	FRealCurve *ArmorPenetrationCurve= CharaterClassInfo->DamageCalculationCoefficient->FindCurve(FName("ArmorPentration"),FString(""));
	// 护甲穿透系数                                                            输入等级
	float ArmorPenetrationCoefficient=ArmorPenetrationCurve->Eval(SourceCombatInterface->GetLevel());
	
	
	
	//有效护甲值  表示忽略一定比例护甲后剩余的护甲值 (每点有效护甲能减免0.3%的伤害)
	float EffectiveArmor=0;
	
	EffectiveArmor=FMath::Max<float>(0,TargetArmor*(100-SourceArmorPenetration*ArmorPenetrationCoefficient)/100);
	//找到曲线后，要指定这个曲线的行名                                                        需要一个上下蚊子串 可以传入一个空的
	FRealCurve *EffectiveArmorCurve= CharaterClassInfo->DamageCalculationCoefficient->FindCurve(FName("EffectiveArmor"),FString(""));
	//有效护甲系数
	float EffectiveArmorCoefficient=EffectiveArmorCurve->Eval(TargetCombatInterface->GetLevel());
	Damage=Damage*(100-EffectiveArmor*EffectiveArmorCoefficient)/100;
	
	
	
	//捕获目标的格挡几率，判断是否成功格挡  格挡成功 伤害减半
	float TargetBlockChance=0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef,EvaluateParameters,TargetBlockChance);
	TargetBlockChance=FMath::Max<float>(0,TargetBlockChance);
	bool bBlocked=FMath::RandRange(1,100)<TargetBlockChance;
	
	//这个是给上下文传值(格挡)
	AuraContext->SetIsBlockedHit(bBlocked);
	//这个是格挡
	if (bBlocked)
	{
		Damage=Damage/2;;
		
	}

	//获取自己的暴击率 
	
	float SourceCriticalHitChance=0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitChanceDef,EvaluateParameters,SourceCriticalHitChance);
	SourceCriticalHitChance=FMath::Max<float>(0,SourceCriticalHitChance);
	bool bCritocaled=FMath::RandRange(1,100)<SourceCriticalHitChance;
	
	
	
	
	//护甲在上面已经减过一次了，这里不能再乘一遍
	//这个是给上下文传值(暴击)
	AuraContext->SetIsCriticalHit(bCritocaled);
	//这个是暴击
	if (bCritocaled)
	{
		//自己的暴击伤害
		float SourceCriticalHitDamage=0;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitDamageDef,EvaluateParameters,SourceCriticalHitDamage);
		SourceCriticalHitDamage=FMath::Max<float>(0,SourceCriticalHitDamage);
		
		//目标的暴击抗性
		float TargetCriticalHitResistance=0;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitResistanceDef,EvaluateParameters,TargetCriticalHitResistance);
		TargetCriticalHitResistance=FMath::Max<float>(0,TargetCriticalHitResistance);
		
		//有效暴击率
		
		//找到曲线后，要指定这个曲线的行名                                                        需要一个上下蚊子串 可以传入一个空的
		FRealCurve *CriticalHitResistanceCurve= CharaterClassInfo->DamageCalculationCoefficient->FindCurve(FName("CriticalHitResistance"),FString(""));
		//有效护甲系数
		float CriticalHitResistanceCoefficient=CriticalHitResistanceCurve->Eval(TargetCombatInterface->GetLevel());
		
		Damage=Damage*2+(SourceCriticalHitDamage-TargetCriticalHitResistance*CriticalHitResistanceCoefficient);
	}

	
	
	
	FGameplayModifierEvaluatedData EvaluateData(UAuraAttributeSet::GetIncomingDamageAttribute(),EGameplayModOp::Additive,Damage);
	
	OutExecutionOutput.AddOutputModifier(EvaluateData);
}
