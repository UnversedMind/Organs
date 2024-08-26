// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bridges/PropertyBridges/PropertyBridge.h"
#include "ObjectPropertyBridge.generated.h"

/**
 * 
 */
UCLASS()
class UIDATATRAVERSAL_API UObjectPropertyBridge : public UPropertyBridge
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	static UObjectPropertyBridge* CreatePropertyBridge(UObject* _ObjectValue);

	UPROPERTY(BlueprintReadOnly)
	UObject* ObjectValue;
	
};
