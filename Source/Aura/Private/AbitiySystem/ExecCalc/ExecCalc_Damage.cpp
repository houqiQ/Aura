// Fill out your copyright notice in the Description page of Project Settings.


#include "AbitiySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "AbitiySystem/AuraAttributeSet.h"

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
	
	AuraDamageStatics()
	{
		//创建并定义了一个名为Armor的属性捕获定义
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,Armor,Target,false);
		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,BlockChance,Target,false);
		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,ArmorPenetration,	Source,false);
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
	
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent*SourceASC=ExecutionParams.GetSourceAbilitySystemComponent();
	
	UAbilitySystemComponent*TargetASC=ExecutionParams.GetTargetAbilitySystemComponent();
	
	AActor*SourceAvActor=SourceASC?SourceASC->GetAvatarActor():nullptr;
	
	AActor*TargetAvActor=TargetASC?TargetASC->GetAvatarActor():nullptr;
	
	FGameplayEffectSpec Spec=ExecutionParams.GetOwningSpec();
	
	
	
	//从源数据和目标数据中收集标签
	const FGameplayTagContainer*SourceTags=Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer*TargetTags=Spec.CapturedTargetTags.GetAggregatedTags();
	
	//捕获属性并获取它的数值大小
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags=SourceTags;
	EvaluateParameters.TargetTags=TargetTags;
	
	
	// 伤害由调用者的幅度设定
	
	//           获取调用者设定的幅度
	float Damage=Spec.GetSetByCallerMagnitude(FAuraGameplayTags::Get().Damage);
	
	
	//护甲
	float TargetArmor=0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef,EvaluateParameters,TargetArmor);
	TargetArmor=FMath::Max<float>(0,TargetArmor);
	
	
	//护甲穿透忽略目标护甲的百分比
	float SourceArmorPenetration=0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef,EvaluateParameters,SourceArmorPenetration);
	SourceArmorPenetration=FMath::Max<float>(0,SourceArmorPenetration);
	
	
	
	//有效护甲值  表示忽略一定比例护甲后剩余的护甲值 (每点有效护甲能减免0.3%的伤害)
	float EffectiveArmor=0;
	
	EffectiveArmor=FMath::Max<float>(0,TargetArmor*(100-SourceArmorPenetration)/100);
	
	Damage=Damage*(100-EffectiveArmor*0.3)/100;
	
	//捕获目标的格挡几率，判断是否成功格挡  格挡成功 伤害减半
	float TargetBlockChance=0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef,EvaluateParameters,TargetBlockChance);
	TargetBlockChance=FMath::Max<float>(0,TargetBlockChance);
	bool bBlocked=FMath::RandRange(1,100)<TargetBlockChance;
	if (bBlocked)
	{
		Damage=Damage/2;;
	}

	FGameplayModifierEvaluatedData EvaluateData(UAuraAttributeSet::GetIncomingDamageAttribute(),EGameplayModOp::Additive,Damage);
	
	OutExecutionOutput.AddOutputModifier(EvaluateData);
}
