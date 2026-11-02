// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "BTService_FindNearesPlayer.generated.h"

/**
 * 它能找出所有玩家控制的角色，定位离它最近的玩家，然后去攻击这个玩家
 */
UCLASS()
class AURA_API UBTService_FindNearesPlayer : public UBTService_BlueprintBase
{
	GENERATED_BODY()
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
