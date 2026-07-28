// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

class UIPutMappingContext;
/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()
	
	
public:
	AAuraCharacter();
	
	virtual void PossessedBy(AController* NewController) override;
	
	virtual void OnRep_PlayerState() override;
	//能力组件初始化
	virtual void InitAbilityActorInfo()override;
	
	
	/*   CombatInterface 接口*/
	virtual int32 GetLevel() override;
	
	/*  End CombatInterface 接口*/
	
	
};
