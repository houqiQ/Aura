// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbitiySystem/Abilities/AuraMyGameplayAbility.h"
#include "AuraDamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraDamageGameplayAbility : public UAuraMyGameplayAbility
{
	GENERATED_BODY()
	
public:
	
	//伤害游戏效果类
	UPROPERTY(EditDefaultsOnly,blueprintReadOnly)
	TSubclassOf<UGameplayEffect>DamageEffectClass;
	
	
	//伤害类型和对应的可随等级或曲线表缩放的浮点数值
	UPROPERTY(EditDefaultsOnly,Category="Damage")
	TMap<FGameplayTag,FScalableFloat>DamageTypes;
};
