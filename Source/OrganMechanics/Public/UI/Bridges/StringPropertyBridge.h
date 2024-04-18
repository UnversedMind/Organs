// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Bridges/PropertyBridge.h"
#include "StringPropertyBridge.generated.h"

/**
 * 
 */
UCLASS()
class ORGANMECHANICS_API UStringPropertyBridge : public UPropertyBridge
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	static UStringPropertyBridge* CreatePropertyBridge(FString _StringValue);

	UPROPERTY(BlueprintReadOnly)
	FString StringValue;
	
};
