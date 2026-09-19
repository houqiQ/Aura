// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacterBase.h"

#include "Aura/Aura.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AAuraCharacterBase::AAuraCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
	//设置是否开启重叠事件
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
	//网格的碰撞响应设置
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile,ECR_Ignore);
	//设置是否开启重叠事件
	GetMesh()->SetGenerateOverlapEvents(true);
	
	Weapon=CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(),TEXT("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AAuraCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAuraCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FVector AAuraCharacterBase::GetCombatSocketLocation()
{
	check(Weapon);
	return Weapon->GetSocketLocation(WeaponTipSocketName);
	
}


UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const 
{
	return AbilitySystemComponent;
}

void AAuraCharacterBase::InitAbilityActorInfo()
{
}

void AAuraCharacterBase::InitializePrimaryAttributes()
{
	FGameplayEffectContextHandle EffectContextHandle=GetAbilitySystemComponent()->MakeEffectContext();
	//EffectContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpecHandle=GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultPrimaryAttributeSet,1,EffectContextHandle);
	
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(),GetAbilitySystemComponent());
}

void AAuraCharacterBase::InitializeSecondaryAttributes()
{
	FGameplayEffectContextHandle EffectContextHandle=GetAbilitySystemComponent()->MakeEffectContext();
	//EffectContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpecHandle=GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultSecondaryAttributeSet,1,EffectContextHandle);
	
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(),GetAbilitySystemComponent());
}

void AAuraCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level)
{
	FGameplayEffectContextHandle EffectContextHandle=GetAbilitySystemComponent()->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpecHandle=GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass,Level,EffectContextHandle);
	
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(),GetAbilitySystemComponent());

}

void AAuraCharacterBase::InitializeDefaultAttributes()
{
	ApplyEffectToSelf(DefaultPrimaryAttributeSet,1);
	
	ApplyEffectToSelf(DefaultSecondaryAttributeSet,1);
	
	ApplyEffectToSelf(DefaultSVitalAttributeSet,1);
}

void AAuraCharacterBase::AddCharacterAbilities()
{
	if (!HasAuthority())return;
	
	
	Cast<UAuraAbilitySystemComponent>(GetAbilitySystemComponent())->AddCharacterAbilities(StartupAbilities);
	
}

UAnimMontage* AAuraCharacterBase::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
	
	
}

void AAuraCharacterBase::Die()
{
	//武器分离(这个是同步的 服务器分离了 客户端也会跟着分离)
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld,true));
	
	MulticastHandleDeath();
}

void AAuraCharacterBase::MulticastHandleDeath_Implementation()
{
	//启动物理模拟
	Weapon->SetSimulatePhysics(true);
	GetMesh()->SetSimulatePhysics(true);
	//启动重力
	Weapon->SetEnableGravity(true);
	GetMesh()->SetSimulatePhysics(true); 
	//启动碰撞
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	//取消碰撞
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Block);
}

