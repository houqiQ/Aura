// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "Attibutinfo.generated.h"

USTRUCT(BlueprintType)
struct FAuraAttributeInfo
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FGameplayTag AttributeTag=FGameplayTag();//标识该信息对应的属性
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText AttributeName=FText();//属性名称的文本
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText AttributeDescription=FText();//属性的描述
	UPROPERTY(BlueprintReadOnly)
	float AttributeValue=0.f;//属性值
};
/**
 * 
 */
UCLASS()
class AURA_API UAttibutinfo : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)//蓝图只读
	TArray<FAuraAttributeInfo>AttributeInformation;
	
	//传入一个游戏标签，能从 AttributeInformation 中找到对应的属性信息返回
	FAuraAttributeInfo FindAttributeInfo(const FGameplayTag& AttributeTag,bool bLogNotFound=false)const;
	
};
