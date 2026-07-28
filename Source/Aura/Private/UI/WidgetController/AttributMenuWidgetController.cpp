// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributMenuWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbitiySystem/AuraAttributeSet.h"

void UAttributMenuWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();
	
	UAuraAttributeSet *AuraAttributeSet=Cast<UAuraAttributeSet>(AttributeSet);
	
	for (auto& Pair:AuraAttributeSet->TagToAttributes)
	{
		
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value.Execute()).AddLambda(
			[this ,Pair,AuraAttributeSet](const FOnAttributeChangeData &Data)
			{
				FAuraAttributeInfo Info=AttributeInfo->FindAttributeInfo(Pair.Key);
				Info.AttributeValue=Pair.Value.Execute().GetNumericValue(AuraAttributeSet);
				AttributeInfoDelegate.Broadcast(Info);
			}
			);
	}
	
}

void UAttributMenuWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();
	UAuraAttributeSet *AuraAttributeSet=Cast<UAuraAttributeSet>(AttributeSet);

 //这个是最简单的 一种方式 通过不停的的复制换变量
	/*if (AuraAttributeSet&&AttributeInfo)
	{
		FGameplayTag GameplayTag=FAuraGameplayTags::Get().Attributes_Primary_Strength;
		
		FAuraAttributeInfo Info=AttributeInfo->FindAttributeInfo(GameplayTag);
		Info.AttributeValue=AuraAttributeSet->GetStrength();
		AttributeInfoDelegate.Broadcast(Info);
	}*/
	
	for (auto Pair:AuraAttributeSet->TagToAttributes)
	{
		FAuraAttributeInfo Info=AttributeInfo->FindAttributeInfo(Pair.Key);
		FGameplayAttribute Attr=Pair.Value.Execute();
		Info.AttributeValue=Attr.GetNumericValue(AuraAttributeSet);
		
		AttributeInfoDelegate.Broadcast(Info);
	}
}
