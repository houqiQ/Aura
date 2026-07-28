// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
/*void UAuraAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) 中
 Data.EvaluatedData 无效  加这个就可以了#include "GameplayEffectExtension.h"*/
#include "AuraAttributeSet.generated.h"

/**
 * 
 */

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
//  有返回值
DECLARE_DELEGATE_RetVal(FGameplayAttribute,FAttributeSignture);
USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()
	FEffectProperties(){}
	
	FGameplayEffectContextHandle EffectContextHandle;
	
	UPROPERTY()
	UAbilitySystemComponent* SourceSAC=nullptr;
	UPROPERTY()
	AActor*SourceActor=nullptr;
	UPROPERTY()
	AController*SourceController=nullptr;
	UPROPERTY()
	ACharacter*SourceCharacter=nullptr;
	
	
	UPROPERTY()
	UAbilitySystemComponent* TargetSAC=nullptr;
	UPROPERTY()
	AActor*TargetActor=nullptr;
	UPROPERTY()
	AController*TargetController=nullptr;
	UPROPERTY()
	ACharacter*TargetCharacter=nullptr;
	
	
};


UCLASS()


class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UAuraAttributeSet();
	
	
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	//NET
	UPROPERTY(ReplicatedUsing=OnRep_Health,BlueprintReadOnly,Category="Vital Attributes")
	//健康
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Health);
	UPROPERTY(ReplicatedUsing=OnRep_MaxHealth,BlueprintReadOnly,Category="Vital Attributes")
	//最大健康
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MaxHealth);
	UFUNCTION()
	void OnRep_Health(FGameplayAttributeData & OldHealth);
	UFUNCTION()
	void OnRep_MaxHealth(FGameplayAttributeData & OldMaxHealth);

	
	UPROPERTY(ReplicatedUsing=OnRep_Mana,BlueprintReadOnly,Category="Vital Attributes")
	//魔力
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Mana);
	UPROPERTY(ReplicatedUsing=OnRep_MaxMana,BlueprintReadOnly,Category="Vital Attributes")
	//最大魔力
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MaxMana);
	
	UFUNCTION()
	void OnRep_Mana(FGameplayAttributeData & OldMana);
	UFUNCTION()
	void OnRep_MaxMana(FGameplayAttributeData & OldMaxMana);
	//这要是属性有变化 都会调用这个函数  
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	// 用这个 (没用上面那个PreAttributeChange)这句话有问题 好像都用了
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
	
	void SetEffectProperties(const struct FGameplayEffectModCallbackData& Data,FEffectProperties&Props);

	UPROPERTY(ReplicatedUsing=OnRep_Strength,BlueprintReadOnly,Category="Primary Attributes")
	FGameplayAttributeData Strength;//力量
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Strength);
	UFUNCTION()
	void OnRep_Strength(FGameplayAttributeData & OldStrength);
	
	UPROPERTY(ReplicatedUsing=OnRep_Intelligence,BlueprintReadOnly,Category="Primary Attributes")
	FGameplayAttributeData Intelligence;//智力
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Intelligence);
	UFUNCTION()
	void OnRep_Intelligence(FGameplayAttributeData & OldIntelligence);
	
	UPROPERTY(ReplicatedUsing=OnRep_Resilience,BlueprintReadOnly,Category="Primary Attributes")
	FGameplayAttributeData Resilience;//韧性
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Resilience);
	UFUNCTION()
	void OnRep_Resilience(FGameplayAttributeData & OldResilience);
	
	UPROPERTY(ReplicatedUsing=OnRep_Vigor,BlueprintReadOnly,Category="Primary Attributes")
	FGameplayAttributeData Vigor;//活力
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Vigor);
	UFUNCTION()
	void OnRep_Vigor(FGameplayAttributeData & OldVigor);
	
	
	UPROPERTY(ReplicatedUsing=OnRep_Armor,BlueprintReadOnly,Category="Secondary Attributes")
	FGameplayAttributeData Armor;//护甲
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Armor);
	UFUNCTION()
	void OnRep_Armor(FGameplayAttributeData & OldArmor);
	
	UPROPERTY(ReplicatedUsing=OnRep_ArmorPenetration,BlueprintReadOnly,Category="Secondary Attributes")
	FGameplayAttributeData ArmorPenetration;//护甲穿透
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,ArmorPenetration);
	UFUNCTION()
	void OnRep_ArmorPenetration(FGameplayAttributeData & OldArmorPenetration);
	
	UPROPERTY(ReplicatedUsing=OnRep_BlockChance,BlueprintReadOnly,Category="Secondary Attributes")
	FGameplayAttributeData BlockChance;//格挡率
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,BlockChance);
	UFUNCTION()
	void OnRep_BlockChance(FGameplayAttributeData & OldBlockChance);
	
	UPROPERTY(ReplicatedUsing=OnRep_CriticalHitChance,BlueprintReadOnly,Category="Secondary Attributes")
	FGameplayAttributeData CriticalHitChance;//暴击率
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,CriticalHitChance);
	UFUNCTION()
	void OnRep_CriticalHitChance(FGameplayAttributeData & OldCriticalHitChance);

	UPROPERTY(ReplicatedUsing=OnRep_CriticalHitDamage,BlueprintReadOnly,Category="Secondary Attributes")
	FGameplayAttributeData CriticalHitDamage;//暴击伤害
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,CriticalHitDamage);
	UFUNCTION()
	void OnRep_CriticalHitDamage(FGameplayAttributeData & OldCriticalHitDamage);
	
	UPROPERTY(ReplicatedUsing=OnRep_CriticalHitResistance,BlueprintReadOnly,Category="Secondary Attributes")
	FGameplayAttributeData CriticalHitResistance;//暴击抗性
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,CriticalHitResistance);
	UFUNCTION()
	void OnRep_CriticalHitResistance(FGameplayAttributeData & OldCriticalHitResistance);
	
	UPROPERTY(ReplicatedUsing=OnRep_HealthRegeneration,BlueprintReadOnly,Category="Secondary Attributes")
	FGameplayAttributeData HealthRegeneration;//生命回复
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,HealthRegeneration);
	UFUNCTION()
	void OnRep_HealthRegeneration(FGameplayAttributeData & OldHealthRegeneration);
	
	UPROPERTY(ReplicatedUsing=OnRep_ManaRegeneration,BlueprintReadOnly,Category="Secondary Attributes")
	FGameplayAttributeData ManaRegeneration;//魔力回复
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,ManaRegeneration);
	UFUNCTION()
	void OnRep_ManaRegeneration(FGameplayAttributeData & OldManaRegeneration);
	
	TMap<FGameplayTag,FAttributeSignture>TagToAttributes;
};



