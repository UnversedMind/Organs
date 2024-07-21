// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bridges/ControlBridges/ControlBridge.h"
#include "IntControlBridge.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FUpdateIntValue, int, newValue);

/**
 * 
 */
UCLASS()
class UIDATATRAVERSAL_API UIntControlBridge : public UControlBridge
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void UpdateValue(int _NewValue);

	virtual void BindFunction(UObject* _FunctionOwner, FName _FunctionName) override;

private:

	FUpdateIntValue UpdateValueDelegate;
	
};
