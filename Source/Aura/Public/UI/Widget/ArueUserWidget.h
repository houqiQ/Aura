// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ArueUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UArueUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;
	
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);
	
	
protected:
	//类似beginplay 的函数
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetConstructorSet();
	
};
