// Fill out your copyright notice in the Description page of Project Settings.


#include "AbitiySystem/Abilities/AuraProjectileSpell.h"

#include "Interaction/CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	
}


void UAuraProjectileSpell::SpawnProjectile(const FVector &ProjectileTargetLocation)
{
	
	//判断自己是否在服务器上
	bool bIsServer=GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;
	ICombatInterface* CombatInterface=Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (!CombatInterface) return;
	FVector ActorLocation=CombatInterface->GetCombatSocketLocation();
	FTransform Transform;
	Transform.SetLocation(ActorLocation);
	// 投射物的旋转 
	FRotator Rotation=(ProjectileTargetLocation-ActorLocation).Rotation();
	//将Z轴归零  飞行物水平飞行
	Rotation.Pitch=0.0f;
	Transform.SetRotation(Rotation.Quaternion());
	AAuraProjectile*Projectile=GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass,Transform,GetOwningActorFromActorInfo(),Cast<APawn>(GetOwningActorFromActorInfo()),ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	
	
	//TODO  给投射物设置一个用于造成伤害的游戏效果规格
	
	
	Projectile->FinishSpawning(Transform);
}


