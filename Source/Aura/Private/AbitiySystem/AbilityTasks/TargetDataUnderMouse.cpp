// Fill out your copyright notice in the Description page of Project Settings.


#include "AbitiySystem/AbilityTasks/TargetDataUnderMouse.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse*Myasd=NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	
	return Myasd;
}

void UTargetDataUnderMouse::Activate()
{
	Super::Activate();
	FHitResult CursorHitResult;
	APlayerController*PC=Ability->GetCurrentActorInfo()->PlayerController.Get();
	PC->GetHitResultUnderCursor(ECC_Visibility,false,CursorHitResult);
	ValidData.Broadcast(CursorHitResult.Location);
	
	
	
	
}
