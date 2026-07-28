// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

UENUM(BlueprintType)
enum class EEffectApplicationPolicy:uint8//应用决策
{
	DoNotApply,//这个不生效
	ApplyOnOverlap,//这个是只有重叠时生效
	ApplyOnEndOverlap,//这个时在重叠结束时生效
	
};

UENUM(BlueprintType)
enum class EEffectRemovePolicy:uint8//应用决策
{
	DoNotRemove,//这个不生效
	RemoveOnEndOverlap,//这个时在重叠结束时生效
	
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAuraEffectActor();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="AppliedEffect")
	EEffectApplicationPolicy InstantEEffectApplicationPolicy;
	
	//这个是实时的游戏效果
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="AppliedEffect")
	TSubclassOf<UGameplayEffect>InstantGameplayEffectClass;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="AppliedEffect")
	EEffectApplicationPolicy DurationEEffectApplicationPolicy;
	//这个是可持续的游戏效果
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="AppliedEffect")
	TSubclassOf<UGameplayEffect>DurationGameplayEffectClass;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="AppliedEffect")
	EEffectApplicationPolicy InfiniteEEffectApplicationPolicy;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="AppliedEffect")
	EEffectRemovePolicy InfiniteEEffectRemovePolicy;
	
	//这个是无限的游戏效果
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="AppliedEffect")
	TSubclassOf<UGameplayEffect>InfiniteGameplayEffectClass;
	//这个是物品等级
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="AppliedEffect")
	float ActorLever=1;
	
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor,TSubclassOf<UGameplayEffect>GameplayEffectClass);
	
	// 这个是 是否要销毁对象
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="AppliedEffect")
	bool bDestroyOnEffectRemoval=false;
	
	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor*TargetActor);
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor*TargetActor);
	
	TMap<FActiveGameplayEffectHandle,UAbilitySystemComponent*>ActiveEffectHandles;

};
