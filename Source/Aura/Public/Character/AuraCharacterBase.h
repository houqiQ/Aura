// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AbitiySystem/AuraAbilitySystemComponent.h"
#include "AbitiySystem/AuraAttributeSet.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"

UCLASS()//,public IAbilitySystemInterface
class AURA_API AAuraCharacterBase : public ACharacter ,public IAbilitySystemInterface ,public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAuraCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere,Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
	//武器上插槽的名称 用于区分 （这个插槽是用于释放魔法）
	UPROPERTY(EditAnywhere,Category="Combat")
	FName WeaponTipSocketName;
	
	//重新接口函数 
	virtual FVector GetCombatSocketLocation() override;
	
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const{return AttributeSet;};
	
	virtual void InitAbilityActorInfo() ;
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Attributes")
	TSubclassOf<UGameplayEffect>DefaultPrimaryAttributeSet;//主属性 用于赋值的
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Attributes")
	TSubclassOf<UGameplayEffect>DefaultSecondaryAttributeSet;//副属性 用于赋值的 （副属性是基于主属性的  主属性一变化 副属性也要变化 所有 是无限效果）
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Attributes")
	TSubclassOf<UGameplayEffect>DefaultSVitalAttributeSet;//生命值 之类的
	
	void InitializePrimaryAttributes();
	
	void InitializeSecondaryAttributes();
	
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass,float Level);
	
	
	void InitializeDefaultAttributes();
	
	
	UPROPERTY(EditAnywhere,Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>>StartupAbilities;//技能数组
	
	
	void AddCharacterAbilities();//添加技能（只应该服务器添加）
	
	
	
	
	
};
