// Fill out your copyright notice in the Description page of Project Settings.


#include "AbitiySystem/AuraAttributeSet.h"
#include "AbitiySystem/AuraAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "GameplayEffect.h" 
#include "Net/UnrealNetwork.h"
#include "GameplayEffectTypes.h" 
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"


UAuraAttributeSet::UAuraAttributeSet()
{
	
	//InitHealth(10);
	//InitMaxHealth(100);
	//InitMana(10);
	//InitMaxMana(100);
	
	FAuraGameplayTags GameplayTags=FAuraGameplayTags::Get();
	
	FAttributeSignture StrengthDelegate;
	StrengthDelegate.BindStatic(GetStrengthAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Primary_Strength,StrengthDelegate);
	
	FAttributeSignture IntelligenceDelegate;
	IntelligenceDelegate.BindStatic(GetIntelligenceAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Primary_Intelligence,IntelligenceDelegate);
	
	FAttributeSignture ResilienceDelegate;
	ResilienceDelegate.BindStatic(GetResilienceAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Primary_Resilience,ResilienceDelegate);
	
	
	FAttributeSignture VigorDelegate;
	VigorDelegate.BindStatic(GetVigorAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Primary_Vigor,VigorDelegate);
	
	FAttributeSignture ArmorDelegate;
	ArmorDelegate.BindStatic(GetArmorAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_Armor,ArmorDelegate);
	
	FAttributeSignture ArmorPenetrationDelegate;
	ArmorPenetrationDelegate.BindStatic(GetArmorPenetrationAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_ArmorPenetration,ArmorPenetrationDelegate);
	
	FAttributeSignture BlockChanceDelegate;
	BlockChanceDelegate.BindStatic(GetBlockChanceAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_BlockChance,BlockChanceDelegate);
	
	FAttributeSignture CriticalHitChanceDelegate;
	CriticalHitChanceDelegate.BindStatic(GetCriticalHitChanceAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitChance,CriticalHitChanceDelegate);
	
	FAttributeSignture CriticalHitDamageDelegate;
	CriticalHitDamageDelegate.BindStatic(GetCriticalHitDamageAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitDamage,CriticalHitDamageDelegate);
	
	FAttributeSignture CriticalHitResistanceDelegate;
	CriticalHitResistanceDelegate.BindStatic(GetCriticalHitResistanceAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitResistance,CriticalHitResistanceDelegate);
	
	
	FAttributeSignture HealthRegenerationDelegate;
	HealthRegenerationDelegate.BindStatic(GetHealthRegenerationAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_HealthRegeneration,HealthRegenerationDelegate);
	
	
	FAttributeSignture ManaRegenerationDelegate;
	ManaRegenerationDelegate.BindStatic(GetManaRegenerationAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_ManaRegeneration,ManaRegenerationDelegate);
	
	FAttributeSignture MaxHealthDelegate;
	MaxHealthDelegate.BindStatic(GetMaxHealthAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_MaxHealth,MaxHealthDelegate);
	
	FAttributeSignture MaxManaDelegate;
	MaxManaDelegate.BindStatic(GetMaxManaAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_Secondary_MaxMana,MaxManaDelegate);
	
	
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Health,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxHealth,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Mana,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxMana,COND_None,REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Strength,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Intelligence,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Resilience,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Vigor,COND_None,REPNOTIFY_Always);
	
	
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Armor,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,ArmorPenetration,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,BlockChance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,CriticalHitChance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,CriticalHitDamage,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,CriticalHitResistance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,HealthRegeneration,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,ManaRegeneration,COND_None,REPNOTIFY_Always);
}

void UAuraAttributeSet::OnRep_Health(FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Health,OldHealth);
}
void UAuraAttributeSet::OnRep_MaxHealth(FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,MaxHealth,OldMaxHealth);
}

void UAuraAttributeSet::OnRep_Mana(FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Mana,OldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(FGameplayAttributeData& OldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,MaxMana,OldMaxMana);
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetHealthAttribute())
	{
		NewValue=FMath::Clamp(NewValue,0,GetMaxHealth());
		//UE_LOG(LogTemp,Warning,TEXT("UAuraAttributeSet::PreAttributeChange中 Health Changed: %f"), NewValue);
	}
	if (Attribute == GetMaxHealthAttribute())
	{
		//UE_LOG(LogTemp,Warning,TEXT("UAuraAttributeSet::PreAttributeChange中 MaxHealth Changed: %f"), NewValue);
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue=FMath::Clamp(NewValue,0,GetMaxMana());
		//UE_LOG(LogTemp,Warning,TEXT("UAuraAttributeSet::PreAttributeChange中 Mana Changed: %f"), NewValue);
	}
	if (Attribute == GetMaxManaAttribute())
	{
		//UE_LOG(LogTemp,Warning,TEXT("UAuraAttributeSet::PreAttributeChange中 MaxMana Changed: %f"), NewValue);
	}
}

void UAuraAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	FEffectProperties Props;
	SetEffectProperties(Data,Props);
	
	if (Data.EvaluatedData.Attribute==GetHealthAttribute())
	{
		
		SetHealth(FMath::Clamp(GetHealth(),0,GetMaxHealth()));
		UE_LOG(LogTemp,Log,TEXT("UAuraAttributeSet::PostGameplayEffectExecute 中Health changed to: %f"),GetHealth());
		
	}
	
	if (Data.EvaluatedData.Attribute==GetManaAttribute())
	{
		
		
		SetMana(FMath::Clamp(GetMana(),0,GetMaxMana()));
		
	}
	
}

void UAuraAttributeSet::SetEffectProperties(const struct FGameplayEffectModCallbackData& Data, FEffectProperties& Props)
{
	FGameplayEffectContextHandle EffectContextHandle=Data.EffectSpec.GetContext();
	Props.EffectContextHandle=EffectContextHandle;
	
	//获取能力组件
	UAbilitySystemComponent*SourceASC=EffectContextHandle.GetInstigatorAbilitySystemComponent();
	Props.SourceSAC=SourceASC;
	
	AActor*SourceAvatarActor=EffectContextHandle.GetInstigatorAbilitySystemComponent()->GetAvatarActor();
	Props.SourceActor=SourceAvatarActor;
	
	AController *SourceController=SourceASC->AbilityActorInfo->PlayerController.Get();
	
	
	
	if (SourceController==nullptr)
	{
		if (APawn*Pawn=Cast<APawn>(SourceAvatarActor))
		{
			SourceController=Pawn->GetController();
		}
		if (SourceController)
		{
			Props.SourceController=SourceController;
			ACharacter*SourceCharater=Cast<ACharacter>(SourceController->GetPawn());
			Props.SourceCharacter=SourceCharater;
			
		}
	}
	
	if (Data.Target.AbilityActorInfo.IsValid()&&Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		AActor*TargeAvatarActor=Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetActor=TargeAvatarActor;
		AController*TargetController=Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetController=TargetController;
		ACharacter*TargetCharacter=Cast<ACharacter>(TargeAvatarActor);
		Props.TargetCharacter=TargetCharacter;
		UAbilitySystemComponent*TargetASC=UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargeAvatarActor);
		Props.TargetSAC=TargetASC;
		
	}
}

void UAuraAttributeSet::OnRep_Strength(FGameplayAttributeData& OldStrength)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Strength,OldStrength);
}

void UAuraAttributeSet::OnRep_Intelligence(FGameplayAttributeData& OldIntelligence)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Intelligence,OldIntelligence);
}

void UAuraAttributeSet::OnRep_Resilience(FGameplayAttributeData& OldResilience)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Resilience,OldResilience);
}

void UAuraAttributeSet::OnRep_Vigor(FGameplayAttributeData& OldVigor)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Vigor,OldVigor);
}

void UAuraAttributeSet::OnRep_Armor(FGameplayAttributeData& OldArmor)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Armor,OldArmor);
}

void UAuraAttributeSet::OnRep_ArmorPenetration(FGameplayAttributeData& OldArmorPenetration)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,ArmorPenetration,OldArmorPenetration);
}

void UAuraAttributeSet::OnRep_BlockChance(FGameplayAttributeData& OldBlockChance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,BlockChance,OldBlockChance);
}

void UAuraAttributeSet::OnRep_CriticalHitChance(FGameplayAttributeData& OldCriticalHitChance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,CriticalHitChance,OldCriticalHitChance);
}

void UAuraAttributeSet::OnRep_CriticalHitDamage(FGameplayAttributeData& OldCriticalHitDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,CriticalHitDamage,OldCriticalHitDamage);
}

void UAuraAttributeSet::OnRep_CriticalHitResistance(FGameplayAttributeData& OldCriticalHitResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,CriticalHitResistance,OldCriticalHitResistance);
}

void UAuraAttributeSet::OnRep_HealthRegeneration(FGameplayAttributeData& OldHealthRegeneration)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,HealthRegeneration,OldHealthRegeneration);
}

void UAuraAttributeSet::OnRep_ManaRegeneration(FGameplayAttributeData& OldManaRegeneration)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,ManaRegeneration,OldManaRegeneration);
}




