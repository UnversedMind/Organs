// Fill out your copyright notice in the Description page of Project Settings.


#include "Functions/FunctionCondition.h"
#include "UObject/NoExportTypes.h"

bool UFunctionCondition::CanUse(UClass* _UseConditionClass, UObject* _Outer, TMap<FName, float> _Variables, int _Slot, int _SecondarySlot, UObject* _RelevantObject, UObject* _SecondaryObject)
{
	UFunctionCondition* _NewCondition = NewObject<UFunctionCondition>(_Outer, _UseConditionClass);
	if (_Outer->GetWorld()) 
	{
		_NewCondition->SetWorldContextObject(_Outer);
	}
	_NewCondition->UpdateFunctionDetailsFromInfo(_Variables);
	return _NewCondition->CanUseInternal(_Slot, _SecondarySlot, _RelevantObject, _SecondaryObject);
}

bool UFunctionCondition::CanUseInternal_Implementation(int _Slot, int _SecondarySlot, UObject* _RelevantObject, UObject* _SecondaryObject)
{
    return true;
}

TMap<FName, float> FConditionInfo::GetPropertiesFromFunctionClass()
{
	TMap<FName, float> propertyNames;
	TObjectPtr<UObject> defaultClassObject = FunctionClass.GetDefaultObject();
	for (TFieldIterator<FProperty> PropertyIterator(FunctionClass); PropertyIterator; ++PropertyIterator)
	{
		if (UFunctionCondition::StaticClass()->HasProperty(*PropertyIterator)) 
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

FName FConditionInfo::GetFunctionClassName()
{
	if (!FunctionClass) 
	{
		return FName();
	}
	return FName(FunctionClass->GetName());
}
