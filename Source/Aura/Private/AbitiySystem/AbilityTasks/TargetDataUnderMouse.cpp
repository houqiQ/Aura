// Fill out your copyright notice in the Description page of Project Settings.


#include "AbitiySystem/AbilityTasks/TargetDataUnderMouse.h"

#include "AbilitySystemComponent.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse*Myasd=NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	
	return Myasd;
}

void UTargetDataUnderMouse::Activate()
{
	Super::Activate();
	
	//这个是不是本地控制(同是否在服务器同理)
	bool bIsLocallyControlled=Ability->GetCurrentActorInfo()->IsLocallyControlled();
	if (bIsLocallyControlled)
	{
		SendMouseCursorData();
	}
	else
	{
		//TODO 在服务器端 要监听目标数据
	}
	
	
	
	
	
	
}

void UTargetDataUnderMouse::SendMouseCursorData()
{
	// 创建一个作用域预测窗口
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());
	
	FGameplayAbilityTargetData_SingleTargetHit*Data= new FGameplayAbilityTargetData_SingleTargetHit();

	FHitResult CursorHitResult;
	APlayerController*PC=Ability->GetCurrentActorInfo()->PlayerController.Get();
	PC->GetHitResultUnderCursor(ECC_Visibility,false,CursorHitResult);
	
	Data->HitResult=CursorHitResult;
	
	/*需要发送到服务器*/
	FGameplayAbilityTargetDataHandle TargetData;
	TargetData.Add(Data);
	
	FGameplayTag ApplicationTag;
	//服务器设置复制目标数据这个函数
	AbilitySystemComponent->ServerSetReplicatedTargetData
	(GetAbilitySpecHandle(),GetActivationPredictionKey(),
		TargetData,ApplicationTag,AbilitySystemComponent->ScopedPredictionKey);
	
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(TargetData);
	}
	
	
}
