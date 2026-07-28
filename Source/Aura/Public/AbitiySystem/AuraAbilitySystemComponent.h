// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags,const FGameplayTagContainer&/*资产标签*/);

UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	//UAbilitySystemComponent*, const FGameplayEffectSpec&, FActiveGameplayEffectHandle
	
	UFUNCTION(Client,Reliable)
	void Client_EffectApplied(UAbilitySystemComponent*AbilitySystemComponent, const FGameplayEffectSpec&EffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle);

public:
	void AbilityActorInfoSet();
	
	FEffectAssetTags EffectAssetTags;
	
	//添加技能
	void AddCharacterAbilities(TArray<TSubclassOf<UGameplayAbility>>StartupAbilities);
	
	//输入被按下
	void AbilityInputTagHeld(FGameplayTag & InputTag);
	//输入被松开
	void AbilityInputTagReleased(FGameplayTag & InputTag);
};
