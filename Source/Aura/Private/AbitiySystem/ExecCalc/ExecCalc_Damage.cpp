// Fill out your copyright notice in the Description page of Project Settings.


#include "AbitiySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "AbitiySystem/AuraAttributeSet.h"

//这个只是在这个类里面用 不用反射
struct AuraDamageStatics
{
	//宏  DECLARE_ATTRIBUTE_CAPTUREDEF 是 GAS 里的一个“声明宏”，用于告诉系统：“我要捕获某个属性”。它需要配合 DEFINE_ATTRIBUTE_CAPTUREDEF 一起使用，一个负责“声明变量”，另一个负责“给变量赋值”
	
	//护甲
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	
	AuraDamageStatics()
	{
		//创建并定义了一个名为Armor的属性捕获定义
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,Armor,Target,false);
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
	float Armor=0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef,EvaluateParameters,Armor);
	Armor=FMath::Max<float>(0,Armor);
	//这个是为了防止等于零（应该）
	Armor++;
	FGameplayModifierEvaluatedData EvaluateData(DamageStatics().ArmorProperty,EGameplayModOp::Additive,Armor);
	
	OutExecutionOutput.AddOutputModifier(EvaluateData);
}
