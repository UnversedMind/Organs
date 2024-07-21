// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bridges/Bridge.h"
#include "ControlBridge.generated.h"

/**
 * 
 */
UCLASS()
class UIDATATRAVERSAL_API UControlBridge : public UBridge
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	static UControlBridge* CreateControlBridge(UObject* _FunctionOwner, FName _FunctionName, TSubclassOf<UControlBridge> _ChildType);

	UFUNCTION(BlueprintPure, meta = (DeterminesOutputType = "_Class"))
	UControlBridge* GetAs(TSubclassOf<UControlBridge> _Class, bool& _Success);

	template <typename T = UControlBridge>
	T* GetAs(TSubclassOf<T> _Class, bool& _Success)
	{
		_Success = this->GetClass()->IsChildOf(_Class);
		return Cast<T>(_Class);
	}

protected:

	virtual void BindFunction(UObject* _FunctionOwner, FName _FunctionName);
	
};
