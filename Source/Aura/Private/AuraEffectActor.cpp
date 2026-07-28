// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

#include "AbilitySystemInterface.h"
#include "AbitiySystem/AuraAttributeSet.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));

}



// Called when the game starts or when spawned
void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	//获取能力组件
	UAbilitySystemComponent*TragetASC=UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TragetASC==nullptr)return;
	check(GameplayEffectClass);
	FGameplayEffectContextHandle EffectContextHandle=TragetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpecHandle=TragetASC->MakeOutgoingSpec(GameplayEffectClass,ActorLever,EffectContextHandle);
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle=TragetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	
	// 获取 游戏效果是不是无限的
	bool bIsInfinite=EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy==EGameplayEffectDurationType::Infinite;
	if (bIsInfinite&&InfiniteEEffectRemovePolicy==EEffectRemovePolicy::RemoveOnEndOverlap)
	{
		ActiveEffectHandles.Add(ActiveGameplayEffectHandle,TragetASC);
	}
	
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	//实时的游戏效果 只有重叠时生效
	if (InstantEEffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,InstantGameplayEffectClass);
	}
	//可持续的游戏效果     这个时间到了效果会自己消失
	if (DurationEEffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,DurationGameplayEffectClass);
	}
	//无限的游戏效果  只有重叠时生效
	if (InfiniteEEffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,InfiniteGameplayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	//实时的游戏效果  重叠结束时生效
	if (InstantEEffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,InstantGameplayEffectClass);
	}
	
	//可持续的游戏效果     这个时间到了效果会自己消失
	if (DurationEEffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,DurationGameplayEffectClass);
	}
	//无限的游戏效果  重叠结束时生效
	if (InfiniteEEffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,InfiniteGameplayEffectClass);
	}
	
	
	
	//下面是移除游戏效果
	if (InfiniteEEffectRemovePolicy==EEffectRemovePolicy::RemoveOnEndOverlap)
	{
		//获取能力组件
		UAbilitySystemComponent*TragetASC=UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (TragetASC==nullptr)return;
		
		
		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		
		for (auto HandlePair:ActiveEffectHandles)
		{
			if(HandlePair.Value==TragetASC)
			{
				TragetASC->RemoveActiveGameplayEffect(HandlePair.Key,1);
				HandlesToRemove.Add(HandlePair.Key);
			}
		}

		for (auto Handle:HandlesToRemove)
		{
			ActiveEffectHandles.FindAndRemoveChecked(Handle);
		}
	}
}

// Called every frame

