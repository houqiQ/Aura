// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/AuraProjectile.h"

AAuraProjectile::AAuraProjectile()
{
	//不使用Tick
	PrimaryActorTick.bCanEverTick=false;
	
	Sphere=CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);//只检测
	//让它忽略所有通道，除了我想让它重叠的几个通道
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	
	ProjectileMovementComponent=CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->InitialSpeed=550;
	ProjectileMovementComponent->MaxSpeed=550;
	//不受重量影响
	ProjectileMovementComponent->ProjectileGravityScale=0.0f;
}

void AAuraProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void AAuraProjectile::BeginPlay()
{
	AActor::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraProjectile::OnOverlap);
}

