// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Bridges/PropertyBridge.h"
#include "IntPropertyBridge.generated.h"

/**
 * 
 */
UCLASS()
class ORGANMECHANICS_API UIntPropertyBridge : public UPropertyBridge
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	static UIntPropertyBridge* CreatePropertyBridge(int _IntValue);

	UPROPERTY(BlueprintReadOnly)
	int IntValue;
	
};
