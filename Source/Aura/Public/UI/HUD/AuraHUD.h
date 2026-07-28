// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/Widget/ArueUserWidget.h"
#include "UI/WidgetController/AttributMenuWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AuraHUD.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
	UPROPERTY()
	TObjectPtr<UArueUserWidget> OverlayWidget;
	
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UArueUserWidget>OverlayWidgetClass;
	
public:
	UOverlayWidgetController* GetOverlayWighetController(FWidgetControllerParams WCParams);
	
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController>OverlayWidgetController;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController>OverlayWidgetControllerClass;
	
	void IintOverlay(APlayerController*PC, APlayerState*PS,UAbilitySystemComponent*ASC,UAttributeSet*AS);
	//储存实际的属性菜单控制器
	UPROPERTY()
	TObjectPtr<UAttributMenuWidgetController> AttributMenuWidgetController;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributMenuWidgetController> AttributMenuWidgetControllerClass;//属性菜单控制器的一个同类型T模板子类
	
	//获取或构建属性菜单控件器
	UAttributMenuWidgetController* GetAttributMenuWighetController(FWidgetControllerParams WCParams);
};
