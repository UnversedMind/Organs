// Fill out your copyright notice in the Description page of Project Settings.


#include "Bridges/ControlBridges/StringControlBridge.h"

void UStringControlBridge::UpdateValue(FString _NewValue)
{
	UpdateValueDelegate.ExecuteIfBound(_NewValue);
}

void UStringControlBridge::BindFunction(UObject* _FunctionOwner, FName _FunctionName)
{
	UpdateValueDelegate.BindUFunction(_FunctionOwner, _FunctionName);
}
