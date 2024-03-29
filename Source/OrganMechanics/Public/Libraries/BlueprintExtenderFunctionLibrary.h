// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BlueprintExtenderFunctionLibrary.generated.h"

/**
 * Additional blueprint functions
 */
UCLASS()
class ORGANMECHANICS_API UBlueprintExtenderFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	//Converts camel case to text with spaces (e.g. CamelCase would become Camel Case)
	UFUNCTION(BlueprintPure)
	static FString ConvertCamelCaseToSpaces(FString _InputString);
	
};
