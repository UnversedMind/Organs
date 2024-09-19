// Fill out your copyright notice in the Description page of Project Settings.


#include "Functions/FunctionBase.h"

UObject* UFunctionBase::GetWorldContextObject()
{
	return WorldContextObject;
}

void UFunctionBase::SetWorldContextObject(UObject* _WorldContextObject)
{
	WorldContextObject = _WorldContextObject;
}

void UFunctionBase::UpdateFunctionDetailsFromInfo(TMap<FName, float> _Variables)
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
