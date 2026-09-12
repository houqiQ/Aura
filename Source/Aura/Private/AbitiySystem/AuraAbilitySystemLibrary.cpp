// Fill out your copyright notice in the Description page of Project Settings.


#include "AbitiySystem/AuraAbilitySystemLibrary.h"

#include "Game/AuraGameModeBase.h"
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

void UAuraAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject,ECharacterClass CharacterClass, float Level,UAbilitySystemComponent*ASC)
{
	//因为敌方的职业信息在游戏模式 
	AAuraGameModeBase*AGMB=Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (AGMB==nullptr)return;
	
	AActor*AvatarActor=ASC->GetAvatarActor();
	
	FGameplayEffectContextHandle ContextHandle =ASC->MakeEffectContext();
	ContextHandle .AddSourceObject(AvatarActor);
	
	FCharacterClassDefaultInfo ClassDefaultInfo=AGMB->CharaterClassInfo->GetCharacterClassInformation(CharacterClass);
	//施加一个游戏效果
	FGameplayEffectSpecHandle PrimaryAttributesSpecHandle=ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes,Level,ContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());
	
	FGameplayEffectSpecHandle SecondaryAttributesSpecHandle=ASC->MakeOutgoingSpec(AGMB->CharaterClassInfo->SecondaryAttributes,Level,ContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());
	
	FGameplayEffectSpecHandle SVitalAttributesSpecHandle=ASC->MakeOutgoingSpec(AGMB->CharaterClassInfo->VitalAttributes,Level,ContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SVitalAttributesSpecHandle.Data.Get());
	
}
