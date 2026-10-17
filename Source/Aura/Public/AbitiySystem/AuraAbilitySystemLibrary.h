// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/CharaterClassInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UI/WidgetController/AttributMenuWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AuraAbilitySystemLibrary.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	//获取已经存在的覆盖小部件控制器                                  变量是 世界上下文对象
	UFUNCTION(BlueprintPure,Category="AuraAbilitySystemLibrary|WidgetController")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);
	
	//获取属性菜单控件控制器
	UFUNCTION(BlueprintPure,Category="AuraAbilitySystemLibrary|WidgetController")
	static UAttributMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);
	UFUNCTION(BlueprintCallable,Category="AuraAbilitySystemLibrary|CharacterClassDefault")
	//这个函数会基于角色类别和等级初始化默认属性
	static void InitializeDefaultAttributes(const UObject* WorldContextObject,ECharacterClass CharacterClass,float Level,UAbilitySystemComponent*ASC);
	
	//初始化敌人的游戏能力
	UFUNCTION(BlueprintCallable,Category="AuraAbilitySystemLibrary|CharacterClassDefault")
	static void GiveStartupAbilities(const UObject* WorldContextObject,UAbilitySystemComponent*ASC);
	
	//返回数据资源
	UFUNCTION(BlueprintCallable,Category="AuraAbilitySystemLibrary|CharacterClassDefault")
	static UCharaterClassInfo*GetCharaterClassInfo(const UObject* WorldContextObject);
	
	//访问AuraGameplayEffectContextd的是否格挡(可蓝图虚函数)
	UFUNCTION(BlueprintPure,Category="AuraAbilitySystemLibrary|GameplayEffect")
	static bool IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle);
	//访问AuraGameplayEffectContextd的是否暴击(可蓝图虚函数)
	UFUNCTION(BlueprintPure,Category="AuraAbilitySystemLibrary|GameplayEffect")
	static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);
	
	//设置AuraGameplayEffectContextd的是否格挡(蓝图可调用)
	UFUNCTION(BlueprintCallable,Category="AuraAbilitySystemLibrary|GameplayEffect")
	static void SetIsBlockedHit(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle,bool bInIsBlockedHit);
	
	//设置AuraGameplayEffectContextd的是否暴击(蓝图可调用)
	UFUNCTION(BlueprintCallable,Category="AuraAbilitySystemLibrary|GameplayEffect")
	static void SetIsCriticalHit(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle,bool bInIsCriticalHit);
	
	
	
	
};
