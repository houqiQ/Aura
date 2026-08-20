// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraSystem.h"
#include "AuraProjectile.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraProjectile: public AActor
{
	GENERATED_BODY()
public:
	AAuraProjectile();
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;
	
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent,AActor*OtherActor,UPrimitiveComponent*OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult);
	
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent>ProjectileMovementComponent;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem>ImpactEffect;//撞击特效
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase>ImpactSound;//撞击声音
	
	//是否碰撞   //用于   //有一种情况 就是销毁动作会同步到客户端 但客户端还没有来得及调用重叠函数 结果就是投射物会在播放音效和生成特效前就被销毁了
	bool bHit=false;
	virtual void Destroyed() override;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase>LoopingSound;//持续的声音
	UPROPERTY()
	TObjectPtr<UAudioComponent>LoopingSoundComponent;//这个是为了控制持续的声音 的播放 
	
	//生命周期
	UPROPERTY(EditDefaultsOnly)
	float LiftSpan=15.f;
};
