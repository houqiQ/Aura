// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/AuraInputConfig.h"

UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (auto AbilityInputAction:AbilityInputActions)
	{
		if (AbilityInputAction.InputTag == InputTag)
		{
			return AbilityInputAction.InputAction;
		}
	}
	
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT(" UAuraInputConfig::FindAbilityInputActionForTag中     没有找到 AbilityInputAction for tag %s on AuraInputConfig %s"), *InputTag.ToString(), *GetName());
	}
	return nullptr;
}
