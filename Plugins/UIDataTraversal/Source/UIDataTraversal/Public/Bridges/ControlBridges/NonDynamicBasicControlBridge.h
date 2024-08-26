// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bridges/ControlBridges/ControlBridge.h"
#include "NonDynamicBasicControlBridge.generated.h"

DECLARE_DELEGATE_FourParams(FOnExecute, int, int, UObject*, UObject*);

/**
 * 
 */
UCLASS()
class UIDATATRAVERSAL_API UNonDynamicBasicControlBridge : public UControlBridge
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void Execute(int _Slot, int _SecondarySlot, UObject* _RelevantObject, UObject* _SecondaryObject);

	virtual void BindFunction(UObject* _FunctionOwner, FName _FunctionName) override;

private:

	FOnExecute ExecuteDelegate;

	
};
