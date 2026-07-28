// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 *  游戏标签
 *  这是一个包含原生游戏标签的单例
 */
struct FAuraGameplayTags
{
public:
	static  FAuraGameplayTags& Get(){return GameplayTags;}
	
	static void InitializeNativeTags();
	//游戏标签变量
	FGameplayTag Attributes_Secondary_Armor;//护甲
	FGameplayTag Attributes_Secondary_ArmorPenetration;//护甲穿透
	FGameplayTag Attributes_Secondary_BlockChance;//格挡率
	FGameplayTag Attributes_Secondary_CriticalHitChance;//暴击率
	FGameplayTag Attributes_Secondary_CriticalHitDamage;//暴击伤害
	FGameplayTag Attributes_Secondary_CriticalHitResistance;//暴击抗性
	FGameplayTag Attributes_Secondary_HealthRegeneration;//生命回复
	FGameplayTag Attributes_Secondary_ManaRegeneration;//魔力回复
	FGameplayTag Attributes_Secondary_MaxHealth;//最大生命值
	FGameplayTag Attributes_Secondary_MaxMana;//最大魔力值
	
	FGameplayTag Attributes_Primary_Strength;//力量
	FGameplayTag Attributes_Primary_Intelligence;//智力
	FGameplayTag Attributes_Primary_Resilience;//韧性
	FGameplayTag Attributes_Primary_Vigor;//活力
	
	FGameplayTag InputTag_LMB;//左鼠标
	FGameplayTag InputTag_RMB;//右鼠标
	FGameplayTag InputTag_1;//按键1
	FGameplayTag InputTag_2;//按键2
	FGameplayTag InputTag_3;//按键3
	FGameplayTag InputTag_4;//按键4
	
	
private:
	static  FAuraGameplayTags GameplayTags;
};
