// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Functions/FunctionCondition.h"
#include "Functions/FunctionExecution.h"
#include "FunctionListInfo.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType, Blueprintable)
struct FFunctionDataInternalValue
{
	GENERATED_BODY()

public:

	FFunctionDataInternalValue() 
	{
		Value = 0.0f;
	}

	FFunctionDataInternalValue(float _Value)
	{
		Value = _Value;
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Value;

};

USTRUCT(BlueprintType, Blueprintable)
struct FFunctionDataInternal
{
	GENERATED_BODY()

public:

	void UpdateAdditionalData(TMap<FName, float> _AdditionalDataTypes)
	{
		TArray<FName> additionalDataNames;
		AdditionalData.GenerateKeyArray(additionalDataNames);

		for (FName additionalDataName : additionalDataNames)
		{
			if (_AdditionalDataTypes.Contains(additionalDataName))
			{
				continue;
			}
			AdditionalData.Remove(additionalDataName);
		}

		for (TPair<FName, float> dataTypeName : _AdditionalDataTypes)
		{
			if (AdditionalData.Contains(dataTypeName.Key))
			{
				continue;
			}
			AdditionalData.Add(dataTypeName.Key, FFunctionDataInternalValue(dataTypeName.Value));
		}
	}

	FFunctionDataInternal()
	{

	}

	FFunctionDataInternal(TMap<FName, float> _NewAdditionalData)
	{
		UpdateAdditionalData(_NewAdditionalData);
	}

	TMap<FName, float> GetAdditionalData() 
	{
		TMap<FName, float> dataToReturn;
		for (TPair<FName, FFunctionDataInternalValue> initialData : AdditionalData) 
		{
			dataToReturn.Add(initialData.Key, initialData.Value.Value);
		}
		return dataToReturn;
	}

	//The map of Variable name to the ideal variable value (e.g. HP:50.0f)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (ReadOnlyKeys, ForceInlineRow, NoResetToDefault, ShowOnlyInnerProperties, FullyExpand="true"))
	TMap<FName, FFunctionDataInternalValue> AdditionalData;
};

USTRUCT(BlueprintType, Blueprintable)
struct FFunctionData
{
	GENERATED_BODY()

public:

	void SetConditionalData(TArray<FConditionInfo> _ConditionalInfo)
	{
		TMap<FName, FFunctionDataInternal> conditionalData;
		for (FConditionInfo conditionInfo : _ConditionalInfo)
		{
			FName conditionName = conditionInfo.GetFunctionClassName();
			TMap<FName, float> propertyNames = conditionInfo.GetPropertiesFromFunctionClass();
			FFunctionDataInternal newConditionalData = FFunctionDataInternal(propertyNames);
			conditionalData.Add(conditionName, newConditionalData);
		}
		ConditionalData = conditionalData;
	}

	void SetExecutableData(TArray<FExecutionInfo> _ExecutionInfo)
	{
		TMap<FName, FFunctionDataInternal> executableData;
		for (FExecutionInfo executionInfo : _ExecutionInfo)
		{
			FName executionName = executionInfo.GetFunctionClassName();
			TMap<FName, float> propertyNames = executionInfo.GetPropertiesFromFunctionClass();
			FFunctionDataInternal newExecutableData = FFunctionDataInternal(propertyNames);
			executableData.Add(executionName, newExecutableData);
		}
		ExecutableData = executableData;
	}

	FFunctionData()
	{

	}

	FFunctionData(TArray<FConditionInfo> _ConditionalInfo, TArray<FExecutionInfo> _ExecutionInfo) 
	{
		SetConditionalData(_ConditionalInfo);
		SetExecutableData(_ExecutionInfo);
	}

	FFunctionData(TMap<FName, FFunctionDataInternal> _ConditionalData, TMap<FName, FFunctionDataInternal> _ExecutableData)
	{
		ConditionalData = _ConditionalData;
		ExecutableData = _ExecutableData;
	}

	//The map of Variable name to the ideal variable value (e.g. HP:50.0f)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (ReadOnlyKeys, ForceInlineRow, NoResetToDefault))
	TMap<FName, FFunctionDataInternal> ConditionalData;

	//The map of Variable name to the ideal variable value (e.g. HP:50.0f)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (ReadOnlyKeys, ForceInlineRow, NoResetToDefault))
	TMap<FName, FFunctionDataInternal> ExecutableData;
};