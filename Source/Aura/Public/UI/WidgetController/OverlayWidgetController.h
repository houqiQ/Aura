// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/ArueUserWidget.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

/**
 * 
*/

USTRUCT(BlueprintType)
//: public FTableRowBase  有这个好像可以在数据列表哪找到
struct FUIWidgetRow: public FTableRowBase 
{
	GENERATED_BODY()
	
	
	//初始化
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FGameplayTag MessageTag=FGameplayTag();
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FText Message;
	
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<UArueUserWidget> MessageWidget;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	
	UTexture2D* Image;
	
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealtChangedSignature,float,NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealtChangedSignature,float,NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature,float,NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature,float,NewMaxMana);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature,FUIWidgetRow,Row);




UCLASS(BlueprintType,Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
	
public:
	virtual void BroadcastInitialValues() override;
	
	virtual void BindCallbacksToDependencies() override;

	
	
	//BlueprintAssignable 这个委托就可以在蓝图中被绑定和触发。
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnHealtChangedSignature OnHealtChanged;
	
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnMaxHealtChangedSignature OnMaxHealtChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnManaChangedSignature OnManaChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnMaxManaChangedSignature OnMaxManaChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FMessageWidgetRowSignature MessageWidgetRowDelegate;
	
	//委托的绑定事件 
	void HealthChangde(const FOnAttributeChangeData& Data);
	//委托的绑定事件
	void MaxHealthChangde(const FOnAttributeChangeData& Data);
	
	//委托的绑定事件 
	void ManaChangde(const FOnAttributeChangeData& Data);
	//委托的绑定事件
	void MaxManaChangde(const FOnAttributeChangeData& Data);
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="WidgetData")
	TObjectPtr<UDataTable>MessageWidgetDataTable;

	template<typename T>
	T*GetDataTableRowByTag(UDataTable*DataTable,const FGameplayTag& Tag);
	
};

template <typename T>
T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	T*Row=DataTable->FindRow<T>(Tag.GetTagName(),TEXT(""));
	
	if (Row)
	{
		return Row;
	}
	return nullptr;
}
