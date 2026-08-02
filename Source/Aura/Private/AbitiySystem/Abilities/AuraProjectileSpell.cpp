// Fill out your copyright notice in the Description page of Project Settings.


#include "AbitiySystem/Abilities/AuraProjectileSpell.h"

#include "Interaction/CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	//判断自己是否在服务器上
	bool bIsServer=HasAuthority(&ActivationInfo);
	if (!bIsServer) return;
	ICombatInterface* CombatInterface=Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (!CombatInterface) return;
	FVector ActorLocation=CombatInterface->GetCombatSocketLocation();
	FTransform Transform;
	Transform.SetLocation(ActorLocation);
	//TODO 投射物的旋转 
	AAuraProjectile*Projectile=GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass,Transform,GetOwningActorFromActorInfo(),Cast<APawn>(GetOwningActorFromActorInfo()),ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	
	//TODO  给投射物设置一个用于造成伤害的游戏效果规格
	
	
	Projectile->FinishSpawning(Transform);
}
