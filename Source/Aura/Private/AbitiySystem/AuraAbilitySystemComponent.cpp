// Fill out your copyright notice in the Description page of Project Settings.


#include "AbitiySystem/AuraAbilitySystemComponent.h"

#include "AuraGameplayTags.h"
#include "AbitiySystem/Abilities/AuraMyGameplayAbility.h"



void UAuraAbilitySystemComponent::Client_EffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	EffectAssetTags.Broadcast(TagContainer);
}

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToTarget.AddUObject(this,&UAuraAbilitySystemComponent::Client_EffectApplied);
	
	const FAuraGameplayTags&GameplayTags=FAuraGameplayTags::Get();
	
	GEngine->AddOnScreenDebugMessage(-1,10,FColor::Orange,FString::Printf(TEXT("Tag:%s"),*GameplayTags.Attributes_Secondary_Armor.ToString()));
}

void UAuraAbilitySystemComponent::AddCharacterAbilities(TArray<TSubclassOf<UGameplayAbility>>StartupAbilities)
{
	for (auto Ability:StartupAbilities)
	{
		
		
		//  FGameplayAbilitySpec 这个是游戏标签容器
		FGameplayAbilitySpec AbilitySpec=FGameplayAbilitySpec(Ability,1);
		if (UAuraMyGameplayAbility *AuraMyGameplayAbility=Cast<UAuraMyGameplayAbility>(AbilitySpec.Ability))
		{
			//              动态能力标签           
			AbilitySpec.DynamicAbilityTags.AddTag(AuraMyGameplayAbility->StartInputTag);
			GiveAbility(AbilitySpec);
		}
	
		
		
		
		
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagHeld(FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())return;
	//返回游戏能力规格的数组
	for (auto AbilitySpec:GetActivatableAbilities())
	{
		//获取对应的动态能力标签
		if(AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);//不知道这个是干什么的
			//是否是激活状态
			if (!AbilitySpec.IsActive())
			{
				//激活
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
	
}

void UAuraAbilitySystemComponent::AbilityInputTagReleased(FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())return;
	//返回游戏能力规格的数组
	for (auto AbilitySpec:GetActivatableAbilities())
	{
		//获取对应的动态能力标签
		if(AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);//不知道这个是干什么的
			
		
		}
	}
}
