// Fill out your copyright notice in the Description page of Project Settings.


#include "Functions/FunctionExecution.h"

bool UFunctionExecution::Use(UClass* _UseFunctionClass, UObject* _Outer, TMap<FName, float> _Variables, int _Slot, int _SecondarySlot, UObject* _RelevantObject, UObject* _SecondaryObject)
{
	UFunctionExecution* _NewExecution = NewObject<UFunctionExecution>(_Outer, _UseFunctionClass);
	if (_Outer->GetWorld())
	{
		_NewExecution->SetWorldContextObject(_Outer);
	}
	_NewExecution->UpdateFunctionDetailsFromInfo(_Variables);
	return _NewExecution->UseInternal(_Slot, _SecondarySlot, _RelevantObject, _SecondaryObject);
}

bool UFunctionExecution::UseInternal_Implementation(int _Slot, int _SecondarySlot, UObject* _RelevantObject, UObject* _SecondaryObject)
{
	return true;
}

TMap<FName, float> FExecutionInfo::GetPropertiesFromFunctionClass()
{
	TMap<FName, float> propertyNames;
	TObjectPtr<UObject> defaultClassObject = FunctionClass.GetDefaultObject();
	for (TFieldIterator<FProperty> PropertyIterator(FunctionClass); PropertyIterator; ++PropertyIterator)
	{
		if (UFunctionExecution::StaticClass()->HasProperty(*PropertyIterator)) 
		{
			continue;
		}
		if (FDoubleProperty* doubleProperty = CastField<FDoubleProperty>(*PropertyIterator))
		{
			if (double* valuePtr = doubleProperty->ContainerPtrToValuePtr<double>(defaultClassObject))
			{
				propertyNames.Add(*PropertyIterator->GetName(), *valuePtr);
			}
			continue;
		}
		if (FIntProperty* intProperty = CastField<FIntProperty>(*PropertyIterator))
		{
			if (int* valuePtr = intProperty->ContainerPtrToValuePtr<int>(defaultClassObject))
			{
				propertyNames.Add(*PropertyIterator->GetName(), *valuePtr);
			}
			continue;
		}
		if (FFloatProperty* floatProperty = CastField<FFloatProperty>(*PropertyIterator))
		{
			if (float* valuePtr = floatProperty->ContainerPtrToValuePtr<float>(defaultClassObject))
			{
				propertyNames.Add(*PropertyIterator->GetName(), *valuePtr);
			}
			continue;
		}
	}
	return propertyNames;
}

FName FExecutionInfo::GetFunctionClassName()
{
	if (!FunctionClass)
	{
		return FName();
	}
	return FName(FunctionClass->GetName());
}
