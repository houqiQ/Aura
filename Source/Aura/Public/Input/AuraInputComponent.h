// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraInputConfig.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "AuraInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template<class UserClass,typename PressedFncType,typename ReleasedFuncType,typename HeldFuncType>
	//                                                                             PressedFnc 按下函数类型参数        ReleasedFunc 释放函数              HeldFunc 保持函数 
	void BindAbilityInputActions(UAuraInputConfig*InputConfig ,UserClass*Object,PressedFncType PressedFnc,ReleasedFuncType ReleasedFunc,HeldFuncType HeldFunc);
	
};

template <class UserClass, typename PressedFncType, typename ReleasedFuncType, typename HeldFuncType>
void UAuraInputComponent::BindAbilityInputActions(UAuraInputConfig* InputConfig, UserClass* Object,
	PressedFncType PressedFnc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputConfig);
	
	for (auto Action:InputConfig->AbilityInputActions)
	{
		if (Action.InputAction&&Action.InputTag.IsValid())
		{
			
			//按下
			
			if (PressedFnc)
			{
				BindAction(Action.InputAction,ETriggerEvent::Started,Object,PressedFnc,Action.InputTag);
			}
			//结束
			if (ReleasedFunc)
			{
				BindAction(Action.InputAction,ETriggerEvent::Completed,Object,ReleasedFunc,Action.InputTag);
			}
			//持续按下
			if (HeldFunc)
			{
				BindAction(Action.InputAction,ETriggerEvent::Triggered,Object,HeldFunc,Action.InputTag);
			}
			
		}
	}
}
