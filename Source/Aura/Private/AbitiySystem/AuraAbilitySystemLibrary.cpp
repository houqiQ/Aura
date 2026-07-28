// Fill out your copyright notice in the Description page of Project Settings.


#include "AbitiySystem/AuraAbilitySystemLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController *PC=UGameplayStatics::GetPlayerController(WorldContextObject,0))
	{
		if (AAuraHUD*AuraHUD=Cast<AAuraHUD>(PC->GetHUD()))
		{
			AAuraPlayerState*PS=PC->GetPlayerState<AAuraPlayerState>();
			//获取能力组件和属性集
			
			UAbilitySystemComponent *ASC =PS->GetAbilitySystemComponent();
			UAttributeSet *AS=PS->GetAttributeSet();
			FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS);
			return AuraHUD->GetOverlayWighetController(WidgetControllerParams);
		} 
	}
	return nullptr;
}

UAttributMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	if (APlayerController *PC=UGameplayStatics::GetPlayerController(WorldContextObject,0))
	{
		if (AAuraHUD*AuraHUD=Cast<AAuraHUD>(PC->GetHUD()))
		{
			AAuraPlayerState*PS=PC->GetPlayerState<AAuraPlayerState>();
			//获取能力组件和属性集
			
			UAbilitySystemComponent *ASC =PS->GetAbilitySystemComponent();
			UAttributeSet *AS=PS->GetAttributeSet();
			FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS);
			return AuraHUD->GetAttributMenuWighetController(WidgetControllerParams);
		} 
	}
	return nullptr;
}
