// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bridges/PropertyBridges/PropertyBridge.h"
#include "ArrayPropertyBridge.generated.h"

/**
 * 
 */
UCLASS()
class UIDATATRAVERSAL_API UArrayPropertyBridge : public UPropertyBridge
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	static UArrayPropertyBridge* CreatePropertyBridge(TArray<UPropertyBridge*> _Data);

	UPROPERTY(BlueprintReadOnly)
	TArray<UPropertyBridge*> Data;

	UFUNCTION(BlueprintPure)
	UPropertyBridge* GetBridgeFromIndex(int index);
	
};
