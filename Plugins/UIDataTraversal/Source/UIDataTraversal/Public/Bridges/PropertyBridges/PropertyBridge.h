// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bridges/Bridge.h"
#include "PropertyBridge.generated.h"

/**
 * A bridge between the Model and View
 */
UCLASS()
class UIDATATRAVERSAL_API UPropertyBridge : public UBridge
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, meta = (DeterminesOutputType = "_Class"))
	UPropertyBridge* GetAs(TSubclassOf<UPropertyBridge> _Class, bool& _Success);

	template <typename T = UPropertyBridge>
	T* GetAs(TSubclassOf<T> _Class, bool& _Success)
	{
		_Success = this->GetClass()->IsChildOf(_Class);
		return Cast<T>(_Class);
	}
};
