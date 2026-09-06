// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Engine/DataAsset.h"
#include "CharaterClassInfo.generated.h"

/**
 *  数据资产
 *  用来储存所用有相关角色职业的数据
 */

UENUM(BlueprintType)//它能作为蓝图类型
enum class  ECharacterClass:uint8
{
	Elementalist,//魔法师
	Warrior,//战士
	Ranger,//游侠
	 
};

USTRUCT(BlueprintType)
struct FCharacterClassDefaultInfo//职业的基础
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly,Category="Class Defaults")
	TSubclassOf<UGameplayEffect>PrimaryAttributes;//主属性
};
UCLASS()
class AURA_API UCharaterClassInfo : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly,Category="Common Class Defaults")
	TSubclassOf<UGameplayEffect>SecondaryAttributes;//
	
	UPROPERTY(EditDefaultsOnly,Category="Common Class Defaults")
	TSubclassOf<UGameplayEffect>VitalAttributes;//
	UPROPERTY(EditDefaultsOnly,Category="Charater Class Defaults")
	TMap<ECharacterClass,FCharacterClassDefaultInfo>CharacterClassInformation;
	
	FCharacterClassDefaultInfo GetCharacterClassInformation(ECharacterClass CharacterClass);
	
};
