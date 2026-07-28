// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbitiySystem/Data/Attibutinfo.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AttributMenuWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature,const FAuraAttributeInfo&,Info);
/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)
class AURA_API UAttributMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
	
public:
	void BindCallbacksToDependencies() override;
	void BroadcastInitialValues() override;
	
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes") 
	FAttributeInfoSignature AttributeInfoDelegate;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttibutinfo>AttributeInfo;
	
	
	
	
};
