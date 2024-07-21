// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bridges/ControlBridges/ControlBridge.h"
#include "StringControlBridge.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FUpdateStringValue, FString, newValue);

/**
 * 
 */
UCLASS()
class UIDATATRAVERSAL_API UStringControlBridge : public UControlBridge
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void UpdateValue(FString _NewValue);

	virtual void BindFunction(UObject* _FunctionOwner, FName _FunctionName) override;

private:

	FUpdateStringValue UpdateValueDelegate;
	
};
