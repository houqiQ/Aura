// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AuraMyGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraMyGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
	public:
	//输入标签
	UPROPERTY(EditDefaultsOnly,Category="Input")
	FGameplayTag StartInputTag;
	
};
 