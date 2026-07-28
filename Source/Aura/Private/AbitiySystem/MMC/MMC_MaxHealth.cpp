// Fill out your copyright notice in the Description page of Project Settings.


#include "AbitiySystem/MMC/MMC_MaxHealth.h"

#include "AbitiySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	//指定要捕捉的属性
	VigorDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	//指定要捕捉的属性 的来源
	VigorDef.AttributeSource=EGameplayEffectAttributeCaptureSource::Target;
	//是否有快照
	VigorDef.bSnapshot=false;
	
	//将其添加到MMC捕获定义数组中
	RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	//从源数据和目标数据中收集标签
	const FGameplayTagContainer*SourceTags=Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer*TargetTags=Spec.CapturedTargetTags.GetAggregatedTags();
	
	//捕获属性并获取它的数值大小
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags=SourceTags;
	EvaluateParameters.TargetTags=TargetTags;
	float Vigor=0;
	GetCapturedAttributeMagnitude(VigorDef,Spec,EvaluateParameters,Vigor);
	
	Vigor=FMath::Max<float>(Vigor,0);
	
	ICombatInterface*CombatInterface=Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	int32 PlayLevel=CombatInterface->GetLevel();
	return 100+Vigor*0.5+PlayLevel*5; 
}
