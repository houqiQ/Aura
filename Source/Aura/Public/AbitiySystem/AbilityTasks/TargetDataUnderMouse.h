// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "Abilities/GameplayAbility.h"
#include "TargetDataUnderMouse.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMoveTargetDataSignature,const FGameplayAbilityTargetDataHandle& , Data);
/**
 * 
 */

UCLASS()
class AURA_API UTargetDataUnderMouse : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable,Category="Abiliy|Tas",meta=(DisplayName="TargetDataUnderMouse",HidePin="OwningAbility",DefaultToSelf="OwningAbility",BlueprintInternalUseOnly="True"))
	static UTargetDataUnderMouse*CreateTargetDataUnderMouse(UGameplayAbility*OwningAbility);

	UPROPERTY(BlueprintAssignable)
	FMoveTargetDataSignature ValidData;
	
private:
	virtual void Activate() override;
	
	//发送鼠标数据
	void SendMouseCursorData();
	UFUNCTION()
	void OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle&DataHandle,FGameplayTag ActivationTag);
};
