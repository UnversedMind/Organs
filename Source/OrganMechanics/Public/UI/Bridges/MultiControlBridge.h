// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Bridges/ControlBridge.h"
#include "MultiControlBridge.generated.h"

DECLARE_DELEGATE(FOnControlExecutionCompleted);

/**
 * 
 */
UCLASS()
class ORGANMECHANICS_API UMultiControlBridge : public UControlBridge
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	TArray<UControlBridge*> Controls;

	virtual void BindFunction(UObject* _FunctionOwner, FName _FunctionName) override;

	UFUNCTION(BlueprintPure)
	UControlBridge* GetBridgeFromIndex(int index);

	UFUNCTION(BlueprintCallable)
	void CompleteControlExecution();

private:

	FOnControlExecutionCompleted OnControlExecutionCompleted;
};
