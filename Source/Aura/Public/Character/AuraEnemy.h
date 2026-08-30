// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Components/WidgetComponent.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase,public IEnemyInterface
{
	GENERATED_BODY()
public:
	
	AAuraEnemy();
	
	/*  IEnemyInterface 重写的函数  */
	//高亮
	UFUNCTION(Blueprintable)
	virtual  void HighlightActor() override;
	//取消高亮
	UFUNCTION(Blueprintable)
	virtual void UnHighlightActor() override;
	/*  IEnemyInterface 重写的函数  */
	
	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted=false;
	
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="CharaterClassDefaults")
	int32 Level=1;
	
	/*   CombatInterface 接口*/
	virtual int32 GetLevel() override;
	
	/*  End CombatInterface 接口*/
	
	//血量显示
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;
	
	
	UPROPERTY(BlueprintAssignable)//BlueprintAssignable 这个是蓝图可赋值
	FOnHealtChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable)//BlueprintAssignable 这个是蓝图可赋值
	FOnMaxHealtChangedSignature OnMaxHealthChanged;
};
