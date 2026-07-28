// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraGameplayTags.h"

#include "GameplayTagsManager.h"

void FAuraGameplayTags::InitializeNativeTags()
{    //护甲                                                 //标签名字                           //标签提示
	GameplayTags.Attributes_Secondary_Armor=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"),FString("减少受到的伤害，提升格挡几率。"));
	//护甲穿透
	GameplayTags.Attributes_Secondary_ArmorPenetration=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPenetration"),FString("忽略敌方护甲的百分比，提高暴击几率。"));
	//格挡率
	GameplayTags.Attributes_Secondary_BlockChance=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.BlockChance"),FString("有机会减少受到伤害的一半。"));
	//暴击率
	GameplayTags.Attributes_Secondary_CriticalHitChance=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitChance"),FString("有几率使伤害翻倍，并额外获得暴击加成。"));
	//暴击伤害
	GameplayTags.Attributes_Secondary_CriticalHitDamage=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitDamage"),FString("当暴击时会增加额外伤害。"));
	//暴击抗性
	GameplayTags.Attributes_Secondary_CriticalHitResistance=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitResistance"),FString("降低被敌方攻击时的暴击几率。"));
	//生命回复
	GameplayTags.Attributes_Secondary_HealthRegeneration=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegeneration"),FString("每秒的生命回复数量。"));
	//魔力回复
	GameplayTags.Attributes_Secondary_ManaRegeneration=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegeneration"),FString("每秒的魔力回复数量。"));
	//最大生命值
	GameplayTags.Attributes_Secondary_MaxHealth=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"),FString("最大生命值。"));
	//最大魔力值
	GameplayTags.Attributes_Secondary_MaxMana=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"),FString("最大魔力值。"));
	
	//力量
	GameplayTags.Attributes_Primary_Strength=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Strength"),FString("增加物理伤害。"));
	//智力
	GameplayTags.Attributes_Primary_Intelligence=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"),FString("增加魔法伤害。"));
	//韧性
	GameplayTags.Attributes_Primary_Resilience=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Resilience"),FString("增加护甲和护甲穿透。"));
	//活力
	GameplayTags.Attributes_Primary_Vigor=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Vigor"),FString("增加生命值。"));
	
	
	//输入标签
	
	
	//左鼠标
	GameplayTags.InputTag_LMB=
		UGameplayTagsManager::Get().AddNativeGameplayTag
	(FName("InputTag.LMB"),FString("输入标签---左鼠标"));
	
	//右鼠标
	GameplayTags.InputTag_RMB=
		UGameplayTagsManager::Get().AddNativeGameplayTag
	(FName("InputTag.RMB"),FString("输入标签---右鼠标"));
	
	//按键1
	GameplayTags.InputTag_1=
		UGameplayTagsManager::Get().AddNativeGameplayTag
	(FName("InputTag.1"),FString("输入标签---按键1"));
	//按键2
	GameplayTags.InputTag_2=
		UGameplayTagsManager::Get().AddNativeGameplayTag
	(FName("InputTag.2"),FString("输入标签---按键2"));
	//按键3
	GameplayTags.InputTag_3=
		UGameplayTagsManager::Get().AddNativeGameplayTag
	(FName("InputTag.3"),FString("输入标签---按键3"));
	//按键4
	GameplayTags.InputTag_4=
		UGameplayTagsManager::Get().AddNativeGameplayTag
	(FName("InputTag.4"),FString("输入标签---按键4"));
}

FAuraGameplayTags FAuraGameplayTags::GameplayTags;
