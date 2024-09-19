// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Functions/FunctionBase.h"
#include "FunctionExecution.generated.h"

/**
 * 
 */

UCLASS(Blueprintable, BlueprintType)
class FUNCTIONDATABASE_API UFunctionExecution : public UFunctionBase
{
	GENERATED_BODY()

public:

	//Returns true if execution succeeds
	static bool Use(UClass* _UseFunctionClass, UObject* _Outer, TMap<FName, float> _Variables, int _Slot, int _SecondarySlot = -1, UObject* _RelevantObject = nullptr, UObject* _SecondaryObject = nullptr);

	//Returns true if execution succeeds
	UFUNCTION(BlueprintNativeEvent)
	bool UseInternal(int _Slot, int _SecondarySlot = -1, UObject* _RelevantObject = nullptr, UObject* _SecondaryObject = nullptr);
	virtual bool UseInternal_Implementation(int _Slot, int _SecondarySlot = -1, UObject* _RelevantObject = nullptr, UObject* _SecondaryObject = nullptr);
};

USTRUCT(Blueprintable, BlueprintType)
struct FUNCTIONDATABASE_API FExecutionInfo
{
	GENERATED_BODY()

public:

	TMap<FName, float> GetPropertiesFromFunctionClass();

	//The execution function class
	UPROPERTY(EditAnywhere)
	TSubclassOf<UFunctionExecution> FunctionClass;

	FName GetFunctionClassName();

	TMap<FName, float> AdditionalData;
};

USTRUCT(Blueprintable, BlueprintType)
struct FExecutionsInFunction
{
	GENERATED_BODY()
public:
	//The list of functions to execute
	UPROPERTY(EditAnywhere)
	TArray<FExecutionInfo> Functions;
};