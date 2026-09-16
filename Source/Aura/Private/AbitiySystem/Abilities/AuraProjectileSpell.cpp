// Fill out your copyright notice in the Description page of Project Settings.


#include "AbitiySystem/Abilities/AuraProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
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
	
	
	// 给投射物设置一个用于造成伤害的游戏效果规格
	   //把伤害游戏效果绑定到了投射物上
	UAbilitySystemComponent *SourceASC=UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	FGameplayEffectSpecHandle SpecHandle=SourceASC->MakeOutgoingSpec(DamageEffectClass,GetAbilityLevel(),SourceASC->MakeEffectContext());
	FAuraGameplayTags GameplayTags=FAuraGameplayTags::Get();
	 
	//在能力等级上进行评估 (后面的都没太懂)  Damage.AsInteger()这个是想要整数   Damage.EvaluateCurveAtLevel() 这个是需要传曲线表  Damage.GetValueAtLevel(GetAbilityLevel());这个是获取对应等级的值
	float ScaledDamage=Damage.GetValueAtLevel(GetAbilityLevel());
	
	//打印
	GEngine->AddOnScreenDebugMessage(-1,3,FColor::Red,FString::Printf(TEXT("void UAuraProjectileSpell::SpawnProjectile(const FVector &ProjectileTargetLocation) 中 ScaledDamage 为%f"),ScaledDamage));
	 int32 a=Damage.AsInteger(GetAbilityLevel());
	
	
	//使用“由调用者设置”的集合（需要调用能力系统蓝图库）
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle,GameplayTags.Damage,50);
	
	Projectile->DamageEffectSpecHandle=SpecHandle;
	
	Projectile->FinishSpawning(Transform);
}


