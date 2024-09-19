// Fill out your copyright notice in the Description page of Project Settings.


#include "Functions/FunctionInfo.h"

bool UFunctionObject::CanExecuteFunction(int _Slot, int _SecondarySlot, UObject* _RelevantObject, UObject* _SecondaryObject)
{
	bool bSuccess = true;
	for (FConditionInfo conditions : FunctionConditions.Functions)
	{
		bSuccess = bSuccess && UFunctionCondition::CanUse(conditions.FunctionClass, this, conditions.AdditionalData, _Slot, _SecondarySlot, _RelevantObject, _SecondaryObject);
	}
	return bSuccess;
}

bool UFunctionObject::ExecuteFunction(int _Slot, int _SecondarySlot, UObject* _RelevantObject, UObject* _SecondaryObject)
{
	bool bSuccess = true;
	for (FExecutionInfo internalInfo : FunctionExecutions.Functions) 
	{
		bool bUseSuccessful = false;
		bUseSuccessful = UFunctionExecution::Use(internalInfo.FunctionClass, this, internalInfo.AdditionalData, _Slot, _SecondarySlot, _RelevantObject, _SecondaryObject);
		bSuccess = bSuccess && bUseSuccessful;
	}
	return true;
}

void UFunctionObject::SetConditionsAndFunctions(FConditionsInFunction _FunctionConditions, FExecutionsInFunction _FunctionExecutions)
{
	FunctionConditions = _FunctionConditions;
	FunctionExecutions = _FunctionExecutions;
}

void UItemFunctionHelper::BreakFunctionInfoStruct(const FFunctionInfo& _FunctionInfo, UFunctionObject*& _OutFunctionObject)
{
	_OutFunctionObject = NewObject<UFunctionObject>();
	_OutFunctionObject->SetConditionsAndFunctions(_FunctionInfo.FunctionConditions, _FunctionInfo.FunctionExecutions);
}

UFunctionObject* FFunctionInfo::GetFunctionExecutionObject()
{
	if (!FunctionExecutionObject) 
	{
		FunctionExecutionObject = NewObject<UFunctionObject>();
		FunctionExecutionObject->SetConditionsAndFunctions(FunctionConditions, FunctionExecutions);
	}
	return FunctionExecutionObject;
}

void FFunctionInfo::PopulateConditionalInfo(TMap<FName, FFunctionDataInternal> _Variables)
{
	for (TPair<FName, FFunctionDataInternal> variable : _Variables) 
	{
		for (int i = 0; i < FunctionConditions.Functions.Num(); i++) 
		{
			if (variable.Key != FunctionConditions.Functions[i].FunctionClass->GetName())
			{
				continue;
			}
			FunctionConditions.Functions[i].AdditionalData = variable.Value.GetAdditionalData();
		}
	}
}

void FFunctionInfo::PopulateExecutableInfo(TMap<FName, FFunctionDataInternal> _Variables)
{
	for (TPair<FName, FFunctionDataInternal> variable : _Variables)
	{
		for (int i = 0; i < FunctionExecutions.Functions.Num(); i++)
		{
			if (variable.Key != FunctionExecutions.Functions[i].FunctionClass->GetName())
			{
				continue;
			}
			FunctionExecutions.Functions[i].AdditionalData = variable.Value.GetAdditionalData();
		}
	}
}
