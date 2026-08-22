// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/AuraProjectile.h"

#include "NiagaraFunctionLibrary.h"
#include "Aura/Aura.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

AAuraProjectile::AAuraProjectile()
{
	//不使用Tick
	PrimaryActorTick.bCanEverTick=false;
	
	Sphere=CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	Sphere->SetCollisionObjectType(ECC_Projectile);
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
	
	bReplicates = true;        //Actor总开关，必须开
	
	// 投射物移动组件开启复制（可选，保险加上）
	ProjectileMovementComponent->SetIsReplicated(true);
}

void AAuraProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//播放声音
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(),FRotator::ZeroRotator);
	
	//生成一个Niagara系统
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,ImpactEffect,GetActorLocation());
	//关闭循环声音
	LoopingSoundComponent->Stop();
	
	//在服务端销毁
	if (HasAuthority())
	{
		//有一种情况 就是销毁动作会同步到客户端 但客户端还没有来得及调用重叠函数 结果就是投射物会在播放音效和生成特效前就被销毁了
		Destroy();
	}
	else
	{
		bHit=true;
	}
}

void AAuraProjectile::BeginPlay()
{
	AActor::BeginPlay();
	//设置生命周期
	SetLifeSpan(LiftSpan);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraProjectile::OnOverlap);
	//播放声音                                          附加到  GetRootComponent()
	LoopingSoundComponent=UGameplayStatics::SpawnSoundAttached(LoopingSound,GetRootComponent());
	
	
}

void AAuraProjectile::Destroyed()
{
	if (!bHit&&!HasAuthority())
	{
		//播放声音
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(),FRotator::ZeroRotator);
	
		//生成一个Niagara系统
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,ImpactEffect,GetActorLocation());
		//关闭循环声音
		LoopingSoundComponent->Stop();
	}
	Super::Destroyed();
	
}

