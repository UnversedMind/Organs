// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FunctionBase.generated.h"

/**
 * 
 */

UCLASS(Blueprintable, Abstract)
class FUNCTIONDATABASE_API UFunctionBase : public UObject 
{
	GENERATED_BODY()

public:

	//Returns the World Context Object
	UFUNCTION(BlueprintPure)
	UObject* GetWorldContextObject();

	//Sets the World Context Object
	UFUNCTION(BlueprintCallable)
	void SetWorldContextObject(UObject* _WorldContextObject);

protected:

	//Finds FProperties with the associated FName, and updates them with the associated float value
	void UpdateFunctionDetailsFromInfo(TMap<FName, float> _Variables);

private:
	//The world context object to facilitate functions where a WorldContextObject is required inside the ItemFunctionBase
	UObject* WorldContextObject;

};