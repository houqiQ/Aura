// Fill out your copyright notice in the Description page of Project Settings.


#include "AbitiySystem/MMC/MMC_MaxMana.h"

#include "AbitiySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	//指定要捕捉的属性
	IntelligenceDef.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	//指定要捕捉的属性 的来源
	IntelligenceDef.AttributeSource=EGameplayEffectAttributeCaptureSource::Target;
	//是否有快照
	IntelligenceDef.bSnapshot=false;
	
	//将其添加到MMC捕获定义数组中
	RelevantAttributesToCapture.Add(IntelligenceDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	//从源数据和目标数据中收集标签
	const FGameplayTagContainer*SourceTags=Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer*TargetTags=Spec.CapturedTargetTags.GetAggregatedTags();
	
	//捕获属性并获取它的数值大小
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags=SourceTags;
	EvaluateParameters.TargetTags=TargetTags;
	float Intelligence=0;
	GetCapturedAttributeMagnitude(IntelligenceDef,Spec,EvaluateParameters,Intelligence);
	
	Intelligence=FMath::Max<float>(Intelligence,0);
	
	ICombatInterface*CombatInterface=Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	int32 PlayLevel=CombatInterface->GetLevel();
	return 100+Intelligence*2+PlayLevel*10; 
	
	
}
