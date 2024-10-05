// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EventBase.generated.h"

/**
 * 
 */

UCLASS(Blueprintable, Abstract)
class EVENTSYSTEM_API UEventBase : public UObject
{
	GENERATED_BODY()

public:

	//Returns the World Context Object
	UFUNCTION(BlueprintPure)
	UObject* GetWorldContextObject();

	//Sets the World Context Object
	void SetWorldContextObject(UObject* _WorldContextObject);

private:
	//The world context object to facilitate functions where a WorldContextObject is required inside the ItemFunctionBase
	UObject* WorldContextObject;

};