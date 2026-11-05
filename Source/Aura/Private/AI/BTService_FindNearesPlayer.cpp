// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_FindNearesPlayer.h"

#include "AIController.h"
#include "Kismet/GameplayStatics.h"

void UBTService_FindNearesPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	APawn*OwningPawn=AIOwner->GetPawn();
	
	//获取目标标签  （有可能是敌人有可能是宠物）
	FName TargetTag=OwningPawn->ActorHasTag(FName("Player"))? FName ("Enemy") : FName ("Player");
	
	TArray<AActor*> TargetActors;
	UGameplayStatics::GetAllActorsWithTag(OwningPawn,TargetTag,TargetActors);
	
}
