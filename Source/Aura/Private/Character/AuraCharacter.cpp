// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacter.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement=true;
	GetCharacterMovement()->RotationRate=FRotator(0,400,0);
	GetCharacterMovement()->bConstrainToPlane=true;
	GetCharacterMovement()->bSnapToPlaneAtStart=true;
	
	bUseControllerRotationPitch=false;
	bUseControllerRotationRoll=false;
	bUseControllerRotationYaw=false;
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	//这个是给服务器用的（没明白）
	InitAbilityActorInfo();
	AddCharacterAbilities();

}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	//这个是给客户端用的（没明白）
	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	if (AAuraPlayerState*AuraPlayerState=GetPlayerState<AAuraPlayerState>())
	{
		AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState,this);
		AbilitySystemComponent=AuraPlayerState->GetAbilitySystemComponent();
		Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
		AttributeSet=AuraPlayerState->GetAttributeSet();
		
		if (AAuraPlayerController* AuraPlayerController=Cast<AAuraPlayerController>(GetController()))
		{
			if (AAuraHUD*AuraHUD=Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
			{
				AuraHUD->IintOverlay(AuraPlayerController,AuraPlayerState,AbilitySystemComponent,AttributeSet);
			}
		}
		
	}
	//InitializePrimaryAttributes();
	
	InitializeDefaultAttributes();
	
}

int32 AAuraCharacter::GetLevel()
{
	AAuraPlayerState*AuraPlayerState=GetPlayerState<AAuraPlayerState>();
	
		return AuraPlayerState->GetLevel();
	
}
