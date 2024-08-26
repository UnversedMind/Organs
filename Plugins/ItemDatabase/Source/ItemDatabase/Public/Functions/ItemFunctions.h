// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemFunctions.generated.h"

/**
 * 
 */

UCLASS(Blueprintable, Abstract)
class ITEMDATABASE_API UItemFunctionBase : public UObject 
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure)
	UObject* GetWorldContextObject();

	UFUNCTION(BlueprintCallable)
	void SetWorldContextObject(UObject* _WorldContextObject);

protected:

	void UpdateFunctionDetailsFromInfo(TMap<FName, float> _Variables);

private:

	UObject* WorldContextObject;

};

UCLASS(Blueprintable, BlueprintType)
class ITEMDATABASE_API UUseCondition : public UItemFunctionBase
{
	GENERATED_BODY()

public:

	static bool CanUse(UClass* _UseConditionClass, UObject* _Outer, TMap<FName, float> _Variables, int _Slot, int _SecondarySlot = -1, UObject* _RelevantObject = nullptr, UObject* _SecondaryObject = nullptr);

	UFUNCTION(BlueprintNativeEvent)
	bool CanUseInternal(int _Slot, int _SecondarySlot = -1, UObject* _RelevantObject = nullptr, UObject* _SecondaryObject = nullptr);
	virtual bool CanUseInternal_Implementation(int _Slot, int _SecondarySlot = -1, UObject* _RelevantObject = nullptr, UObject* _SecondaryObject = nullptr);
};

UCLASS(Blueprintable, BlueprintType)
class ITEMDATABASE_API UUseFunction : public UItemFunctionBase
{
	GENERATED_BODY()

public:

	static bool Use(UClass* _UseFunctionClass, UObject* _Outer, TMap<FName, float> _Variables, int _Slot, int _SecondarySlot = -1, UObject* _RelevantObject = nullptr, UObject* _SecondaryObject = nullptr);

	UFUNCTION(BlueprintNativeEvent)
	bool UseInternal(int _Slot, int _SecondarySlot = -1, UObject* _RelevantObject = nullptr, UObject* _SecondaryObject = nullptr);
	virtual bool UseInternal_Implementation(int _Slot, int _SecondarySlot = -1, UObject* _RelevantObject = nullptr, UObject* _SecondaryObject = nullptr);
};

USTRUCT(Blueprintable, BlueprintType)
struct FUseConditionInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUseCondition> FunctionClass;

	UPROPERTY(EditAnywhere)
	TMap<FName, float> FunctionInformation;

};

USTRUCT(Blueprintable, BlueprintType)
struct FUseFunctionInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUseFunction> FunctionClass;
		
	UPROPERTY(EditAnywhere)
	TMap<FName, float> FunctionInformation;

};

USTRUCT(Blueprintable, BlueprintType)
struct FConditionsToExecute
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	TArray<FUseConditionInfo> Functions;
};

USTRUCT(Blueprintable, BlueprintType)
struct FFunctionsToExecute 
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	TArray<FUseFunctionInfo> Functions;
};

UCLASS(BlueprintType)
class UFunctionExecution : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION()
	bool CanExecuteFunction(int _Slot, int _SecondarySlot = -1, UObject* _RelevantObject = nullptr, UObject* _SecondaryObject = nullptr);

	UFUNCTION()
	bool ExecuteFunction(int _Slot, int _SecondarySlot = -1, UObject* _RelevantObject = nullptr, UObject* _SecondaryObject = nullptr);

	UFUNCTION()
	void Execute(int _Slot, int _SecondarySlot, UObject* _RelevantObject, UObject* _SecondaryObject)
	{
		if (!CanExecuteFunction(_Slot, _SecondarySlot, _RelevantObject, _SecondaryObject)) {
			return;
		}
		ExecuteFunction(_Slot, _SecondarySlot, _RelevantObject, _SecondaryObject);
	}

	void SetConditionsAndFunctions(FConditionsToExecute _FunctionConditions, FFunctionsToExecute _FunctionExecutions);

private:

	FConditionsToExecute FunctionConditions;

	FFunctionsToExecute FunctionExecutions;
};

USTRUCT(Blueprintable, BlueprintType, meta = (HasNativeBreak = "ItemDatabase.ItemFunctionHelper.BreakFunctionInfoStruct"))
struct FFunctionInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (GetKeyOptions = "InventorySystem.InventorySettings.GetFunctionNames"))
	FName FunctionName;

	UPROPERTY(EditAnywhere, meta = (ShowOnlyInnerProperties))
	FConditionsToExecute FunctionConditions;

	UPROPERTY(EditAnywhere, meta = (ShowOnlyInnerProperties))
	FFunctionsToExecute FunctionExecutions;

	UPROPERTY(BlueprintReadOnly)
	UFunctionExecution* FunctionExecutionObject;
};

USTRUCT(Blueprintable, BlueprintType)
struct FFunctionList 
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FFunctionInfo> Functions;
};

UCLASS(BlueprintType)
class UItemFunctionHelper : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "ItemFunctions", meta = (BlueprintThreadSafe))
	static void BreakFunctionInfoStruct(const FFunctionInfo& _FunctionInfo, FName& _OutName, UFunctionExecution*& _OutExecutionObject);
};