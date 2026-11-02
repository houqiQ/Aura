// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_FindNearesPlayer.h"

#include "AIController.h"

void UBTService_FindNearesPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	GEngine->AddOnScreenDebugMessage(1,1,FColor::Green,*AIOwner->GetName());
	GEngine->AddOnScreenDebugMessage(1,1,FColor::Red,*ActorOwner->GetName());
	
}
