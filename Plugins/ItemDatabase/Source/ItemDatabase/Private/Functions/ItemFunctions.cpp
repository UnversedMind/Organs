// Fill out your copyright notice in the Description page of Project Settings.


#include "Functions/ItemFunctions.h"

UObject* UItemFunctionBase::GetWorldContextObject()
{
	return WorldContextObject;
}

void UItemFunctionBase::SetWorldContextObject(UObject* _WorldContextObject)
{
	WorldContextObject = _WorldContextObject;
}

void UItemFunctionBase::UpdateFunctionDetailsFromInfo(TMap<FName, float> _Variables)
{
	for (TPair<FName, float> variable : _Variables)
	{
		FProperty* property = GetClass()->FindPropertyByName(variable.Key);
		checkf(property, TEXT("Property with name %s not found! Either remove it from the variable list, or add it to your function."), *variable.Key.ToString());
		if (FDoubleProperty* doubleProperty = CastField<FDoubleProperty>(property)) 
		{
			if (double* valuePtr = doubleProperty->ContainerPtrToValuePtr<double>(this))
			{
				*valuePtr = variable.Value;
			}
			return;
		}
		if (FIntProperty* intProperty = CastField<FIntProperty>(property)) 
		{
			if (int* valuePtr = intProperty->ContainerPtrToValuePtr<int>(this)) 
			{
				*valuePtr = variable.Value;
			}
			return;
		}
		if (FFloatProperty* floatProperty = CastField<FFloatProperty>(property)) 
		{
			if (float* valuePtr = floatProperty->ContainerPtrToValuePtr<float>(this))
			{
				*valuePtr = variable.Value;
			}
			return;
		}
	}
}

bool UUseCondition::CanUse(UClass* _UseConditionClass, UObject* _Outer, TMap<FName, float> _Variables, int _Slot, int _SecondarySlot, UObject* _RelevantObject, UObject* _SecondaryObject)
{
	UUseCondition* _NewUseCondition = NewObject<UUseCondition>(_Outer, _UseConditionClass);
	if (_Outer->GetWorld()) 
	{
		_NewUseCondition->SetWorldContextObject(_Outer);
	}
	_NewUseCondition->UpdateFunctionDetailsFromInfo(_Variables);
	return _NewUseCondition->CanUseInternal(_Slot, _SecondarySlot, _RelevantObject, _SecondaryObject);
}

bool UUseCondition::CanUseInternal_Implementation(int _Slot, int _SecondarySlot, UObject* _RelevantObject, UObject* _SecondaryObject)
{
    return true;
}

bool UUseFunction::Use(UClass* _UseFunctionClass, UObject* _Outer, TMap<FName, float> _Variables, int _Slot, int _SecondarySlot, UObject* _RelevantObject, UObject* _SecondaryObject)
{
	UUseFunction* _NewUseFunction = NewObject<UUseFunction>(_Outer, _UseFunctionClass);
	if (_Outer->GetWorld())
	{
		_NewUseFunction->SetWorldContextObject(_Outer);
	}
	_NewUseFunction->UpdateFunctionDetailsFromInfo(_Variables);
	return _NewUseFunction->UseInternal(_Slot, _SecondarySlot, _RelevantObject, _SecondaryObject);
}

bool UUseFunction::UseInternal_Implementation(int _Slot, int _SecondarySlot, UObject* _RelevantObject, UObject* _SecondaryObject)
{
	return true;
}

bool UFunctionExecution::CanExecuteFunction(int _Slot, int _SecondarySlot, UObject* _RelevantObject, UObject* _SecondaryObject)
{
	bool bSuccess = true;
	for (FUseConditionInfo conditions : FunctionConditions.Functions)
	{
		bSuccess = bSuccess && UUseCondition::CanUse(conditions.FunctionClass, this, conditions.FunctionInformation, _Slot, _SecondarySlot, _RelevantObject, _SecondaryObject);
	}
	return bSuccess;
}

bool UFunctionExecution::ExecuteFunction(int _Slot, int _SecondarySlot, UObject* _RelevantObject, UObject* _SecondaryObject)
{
	bool bSuccess = true;
	for (FUseFunctionInfo internalInfo : FunctionExecutions.Functions) 
	{
		bool bUseSuccessful = false;
		bUseSuccessful = UUseFunction::Use(internalInfo.FunctionClass, this, internalInfo.FunctionInformation, _Slot, _SecondarySlot, _RelevantObject, _SecondaryObject);
		bSuccess = bSuccess && bUseSuccessful;
	}
	return true;
}

void UFunctionExecution::SetConditionsAndFunctions(FConditionsToExecute _FunctionConditions, FFunctionsToExecute _FunctionExecutions)
{
	FunctionConditions = _FunctionConditions;
	FunctionExecutions = _FunctionExecutions;
}

void UItemFunctionHelper::BreakFunctionInfoStruct(const FFunctionInfo& _FunctionInfo, FName& _OutName, UFunctionExecution*& _OutExecutionObject)
{
	_OutName = _FunctionInfo.FunctionName;
	_OutExecutionObject = NewObject<UFunctionExecution>();
	_OutExecutionObject->SetConditionsAndFunctions((_FunctionInfo.FunctionConditions), (_FunctionInfo.FunctionExecutions));
}
