// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Functions/FunctionCondition.h"
#include "Functions/FunctionExecution.h"
#include "Functions/FunctionListInfo.h"
#include "FunctionInfo.generated.h"

/**
 * 
 */

UCLASS(BlueprintType)
class UFunctionObject : public UObject
{
	GENERATED_BODY()

public:

	//Returns true if the function conditions all succeeded
	UFUNCTION()
	bool CanExecuteFunction(int _Slot, int _SecondarySlot = -1, UObject* _RelevantObject = nullptr, UObject* _SecondaryObject = nullptr);

	//Returns true if the function executions all succeeded
	UFUNCTION()
	bool ExecuteFunction(int _Slot, int _SecondarySlot = -1, UObject* _RelevantObject = nullptr, UObject* _SecondaryObject = nullptr);

	//Executes the function executions if the function conditions succeeded
	UFUNCTION()
	void Execute(int _Slot, int _SecondarySlot, UObject* _RelevantObject, UObject* _SecondaryObject)
	{
		if (!CanExecuteFunction(_Slot, _SecondarySlot, _RelevantObject, _SecondaryObject)) {
			return;
		}
		ExecuteFunction(_Slot, _SecondarySlot, _RelevantObject, _SecondaryObject);
	}

	//Sets the conditions and functions of this object
	void SetConditionsAndFunctions(FConditionsInFunction _FunctionConditions, FExecutionsInFunction _FunctionExecutions);

private:

	//The list of conditions to execute
	FConditionsInFunction FunctionConditions;

	//The list of functions to execute
	FExecutionsInFunction FunctionExecutions;
};

USTRUCT(Blueprintable, BlueprintType, meta = (HasNativeBreak = "FunctionDatabase.ItemFunctionHelper.BreakFunctionInfoStruct"))
struct FUNCTIONDATABASE_API FFunctionInfo : public FTableRowBase
{
	GENERATED_BODY()

public:

	//The list of function conditions
	UPROPERTY(EditAnywhere, meta = (ShowOnlyInnerProperties))
	FConditionsInFunction FunctionConditions;

	//The list of function executions
	UPROPERTY(EditAnywhere, meta = (ShowOnlyInnerProperties))
	FExecutionsInFunction FunctionExecutions;

	UFunctionObject* GetFunctionExecutionObject();

	void PopulateConditionalInfo(TMap<FName, FFunctionDataInternal> _Variables);

	void PopulateExecutableInfo(TMap<FName, FFunctionDataInternal> _Variables);

private:

	//The function execution object - required as only UObjects can be bound
	UFunctionObject* FunctionExecutionObject;
};

UCLASS(BlueprintType)
class UItemFunctionHelper : public UObject
{
	GENERATED_BODY()

public:
	//Required to ensure that the Function Execution Object is valid
	UFUNCTION(BlueprintPure, Category = "ItemFunctions", meta = (BlueprintThreadSafe))
	static void BreakFunctionInfoStruct(const FFunctionInfo& _FunctionInfo, UFunctionObject*& _OutFunctionObject);
};