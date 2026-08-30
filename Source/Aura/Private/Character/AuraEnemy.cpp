// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraEnemy.h"

AAuraEnemy::AAuraEnemy()
{
	AbilitySystemComponent=CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	
	AbilitySystemComponent->SetIsReplicated(true);
	
	AttributeSet=CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	HealthBar=CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent()); 
}

void AAuraEnemy::HighlightActor()
{
	bHighlighted=true;
	
	//GetMesh()->bRenderCustomDepth=true;
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(250);
	
	Weapon->bRenderCustomDepth=true;
	Weapon->SetCustomDepthStencilValue(250);
	
}

void AAuraEnemy::UnHighlightActor()
{
	bHighlighted=false;
	//GetMesh()->bRenderCustomDepth=false;
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
	
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	InitAbilityActorInfo();
	UAuraAttributeSet*AuraAttributeSet=Cast<UAuraAttributeSet>(AttributeSet);
	if (UArueUserWidget* ArueUserWidget=Cast<UArueUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		ArueUserWidget->SetWidgetController(this);
	}
	
	//绑定委托
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
	{
		OnHealthChanged.Broadcast(Data.NewValue);
	}
	);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
	{
		OnMaxHealthChanged.Broadcast(Data.NewValue);
	}
	);
	//这个是初始化 UI
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	
}

void AAuraEnemy::InitAbilityActorInfo()
{
	Super::InitAbilityActorInfo();
	//设置能力组件的拥有者
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	
	InitializeDefaultAttributes();
	
}

int32 AAuraEnemy::GetLevel()
{
	return Level;
}
