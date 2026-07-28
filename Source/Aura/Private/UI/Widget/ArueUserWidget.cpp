// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/ArueUserWidget.h"

void UArueUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController=InWidgetController;
	WidgetConstructorSet();
}
