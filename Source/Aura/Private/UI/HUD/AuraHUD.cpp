// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/AuraHUD.h"

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();
	
	
}

UOverlayWidgetController* AAuraHUD::GetOverlayWighetController(FWidgetControllerParams WCParams)
{
	
	if (OverlayWidgetController==nullptr)
	{
		OverlayWidgetController=NewObject<UOverlayWidgetController>(this,OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		
		OverlayWidgetController->BindCallbacksToDependencies();
	}
	
	return OverlayWidgetController;
}

void AAuraHUD::IintOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	
	checkf(OverlayWidgetControllerClass,TEXT("AAuraHUD::IintOverlay 中 OverlayWidgetControllerClass 为空 请在蓝图赋值"));
	checkf(OverlayWidgetClass,TEXT("AAuraHUD::IintOverlay 中 OverlayWidgetClass 为空 请在蓝图赋值"));
	
	
	UUserWidget *Widget=CreateWidget<UUserWidget>(GetWorld(),OverlayWidgetClass);
	OverlayWidget=Cast<UArueUserWidget>(Widget);
	
	FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS);
	UOverlayWidgetController*WidgetController=GetOverlayWighetController(WidgetControllerParams);
	
	OverlayWidget->SetWidgetController(WidgetController);
	//
	WidgetController->BroadcastInitialValues();
	
	Widget->AddToViewport();
}

UAttributMenuWidgetController* AAuraHUD::GetAttributMenuWighetController(FWidgetControllerParams WCParams)
{
	if (AttributMenuWidgetController==nullptr)
	{
		//
		AttributMenuWidgetController=NewObject<UAttributMenuWidgetController>(this,AttributMenuWidgetControllerClass);
		AttributMenuWidgetController->SetWidgetControllerParams(WCParams);
		AttributMenuWidgetController->BindCallbacksToDependencies();
	}
	
	return AttributMenuWidgetController;
}
