// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/AuraProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
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
	
	/*  这个是之前大肥鱼改的
	 //注意：这里必须是 Overlap，写成 Ignore 的话球体不会和任何东西产生重叠（敌人是 Pawn）
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);*/
	
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	
	ProjectileMovementComponent=CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->InitialSpeed=550;
	ProjectileMovementComponent->MaxSpeed=550;
	//不受重量影响
	ProjectileMovementComponent->ProjectileGravityScale=0.0f;
	
	bReplicates = true;        //Actor总开关，必须开
	/* 这个是之前大肥鱼改的
	 //投射物是普通 AActor，默认不复制移动（Pawn 才在构造函数里默认开）；不开的话客户端那份拿到位置修正
	SetReplicateMovement(true);
	*/
	
	// 投射物移动组件开启复制（可选，保险加上）
	ProjectileMovementComponent->SetIsReplicated(true);
}

void AAuraProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!DamageEffectSpecHandle.Data.IsValid())
	{
		return;
	}
	
	if (DamageEffectSpecHandle.Data.IsValid()&&DamageEffectSpecHandle.Data.Get()->GetContext().GetEffectCauser()==OtherActor)
	{
		return;
	}
	
	
	if (bHit)
	{
		//播放声音
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(),FRotator::ZeroRotator);
	
		//生成一个Niagara系统
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,ImpactEffect,GetActorLocation());
		if(LoopingSoundComponent)
			//关闭循环声音
				LoopingSoundComponent->Stop();
	}
	
	//播放声音
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, OtherActor->GetActorLocation(),FRotator::ZeroRotator);
	
	//生成一个Niagara系统
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,ImpactEffect,OtherActor->GetActorLocation());
	if(LoopingSoundComponent)
		//关闭循环声音
			LoopingSoundComponent->Stop();
	
	//在服务端销毁
	if (HasAuthority())
	{
		
		
		
		
		//获取重叠对象的能力组件
		if (UAbilitySystemComponent*TargetASC=UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			//将伤害效果的规格句柄应用到这个能力组件          句柄内部携带的数据本身就是一个包装器   DamageEffectSpecHandle.Data.Get()是返回一个指针需要解引用
			TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
		}
		
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
	//UE_LOG(LogTemp, Log, TEXT("AAuraProjectile::BeginPlay() 中RootComponent valid: %d"), IsValid(GetRootComponent()));
	
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
		if(LoopingSoundComponent)
		LoopingSoundComponent->Stop();
	}
	
	Super::Destroyed();
	
}

