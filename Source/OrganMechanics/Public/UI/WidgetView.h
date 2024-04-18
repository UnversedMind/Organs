// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetView.generated.h"

/**
 * 
 */
UCLASS()
class ORGANMECHANICS_API UWidgetView : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveData(const class UPropertyBridge* _Data);

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveControls(const class UControlBridge* _Controls);

	UFUNCTION(BlueprintCallable)
	void SetDataModel(UObject* _NewDataModel);

	UFUNCTION(BlueprintCallable)
	void UpdateDataFromModel();

private:

	UObject* DataModel;
	
};
