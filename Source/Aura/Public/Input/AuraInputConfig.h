// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputAction.h"
#include "Engine/DataAsset.h"
#include "AuraInputConfig.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FAuraInputAction
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAction;//输入动作
	
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag=FGameplayTag();//游戏标签
};
UCLASS()
class AURA_API UAuraInputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<FAuraInputAction>AbilityInputActions;
	
	
	UInputAction*FindAbilityInputActionForTag(const FGameplayTag&InputTag,bool bLogNotFound=false)const;
	
};
