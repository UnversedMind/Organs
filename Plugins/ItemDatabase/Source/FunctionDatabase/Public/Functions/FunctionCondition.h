// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Functions/FunctionBase.h"
#include "FunctionCondition.generated.h"

/**
 * 
 */

UCLASS(Blueprintable, BlueprintType)
class FUNCTIONDATABASE_API UFunctionCondition : public UFunctionBase
{
	GENERATED_BODY()

public:

	//Returns true if condition succeeds
	static bool CanUse(UClass* _UseConditionClass, UObject* _Outer, TMap<FName, float> _Variables, int _Slot, int _SecondarySlot = -1, UObject* _RelevantObject = nullptr, UObject* _SecondaryObject = nullptr);

	//Returns true if condition succeeds
	UFUNCTION(BlueprintNativeEvent)
	bool CanUseInternal(int _Slot, int _SecondarySlot = -1, UObject* _RelevantObject = nullptr, UObject* _SecondaryObject = nullptr);
	virtual bool CanUseInternal_Implementation(int _Slot, int _SecondarySlot = -1, UObject* _RelevantObject = nullptr, UObject* _SecondaryObject = nullptr);
};

USTRUCT(Blueprintable, BlueprintType)
struct FUNCTIONDATABASE_API FConditionInfo
{
	GENERATED_BODY()

public:

	TMap<FName, float> GetPropertiesFromFunctionClass();

	//The condition function class
	UPROPERTY(EditAnywhere)
	TSubclassOf<UFunctionCondition> FunctionClass;

	FName GetFunctionClassName();

	TMap<FName, float> AdditionalData;
};

USTRUCT(Blueprintable, BlueprintType)
struct FConditionsInFunction
{
	GENERATED_BODY()
public:

	//The list of conditions to execute
	UPROPERTY(EditAnywhere)
	TArray<FConditionInfo> Functions;
};