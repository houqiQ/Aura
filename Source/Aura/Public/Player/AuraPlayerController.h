// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraGameplayTags.h"
#include "AbitiySystem/AuraAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInput/Public//InputMappingContext.h"
#include "Input/AuraInputConfig.h"
#include "Interaction/EnemyInterface.h"
#include "AuraPlayerController.generated.h"


//class UInputMappingContext;
/**
 * @class AAuraPlayerController
 * @brief Extends APlayerController to provide specific functionality for the Aura game.
 *
 * This class is designed to handle player input and manage the player's interaction within the game environment,
 * particularly tailored for the needs of the Aura game. It includes an input mapping context for configuring
 * player controls.
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAuraPlayerController();
	virtual void PlayerTick(float DeltaTime) override;
	
	void InitializeSubsystem();
protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext>AureContext;
	
	virtual void SetupInputComponent() override;
	
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction>MoveAction;
	
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction>ShiftAction;
	
	void ShiftPressed();
	
	void ShiftReleased();
	bool bShiftPressed=false;
	
	void Move (const FInputActionValue& InputActionValue);
	//光标追踪
	void CursorTrace();
	
	IEnemyInterface* LastActor;
	IEnemyInterface* ThisActor;
	
	
	UPROPERTY(EditDefaultsOnly,Category="Input")
	TObjectPtr<UAuraInputConfig> InputConfig;//这个是那个数据资产 存有标签和输入动作的
	
	void AbilityInputTagPagPressed(FGameplayTag InputTag);//点击
	void AbilityInputTagReleased(FGameplayTag InputTag);//松开
	void AbilityInputTagHeld(FGameplayTag InputTag);//按住
	//这个是防止多次转化 浪费性能
	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;
	//赋值AuraAbilitySystemComponent
	UAuraAbilitySystemComponent* GetASC();
	
	/*鼠标移动 开始*/
	
	
	FVector CachedDestination=FVector::Zero();//当点击某个位置时，记录当前位置
	float FollowTime=0.f;//记录鼠标按下后的时间 用来判断是断按还是长按
	float ShortPressTime=0.5f;//短按的阈值
	bool bAutoRunning=false;//是否移动
	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius=50.f;//自动运行接受半径的浮点数
	UPROPERTY(VisibleAnywhere)//随处可见
	TObjectPtr<USplineComponent> Spline;//样条线  （在构造函数里初始化）
	bool bTargeting=false;//鼠标书否移动到敌人身上 (用来区分是移动还是攻击)  (当鼠标左键按下时就开始检测)
	
	void AutoRun();
	
	//光标命中结果	(高亮显示中也用到了)
	FHitResult CursorHitResult;
	
	/*鼠标移动 结束*/
};
