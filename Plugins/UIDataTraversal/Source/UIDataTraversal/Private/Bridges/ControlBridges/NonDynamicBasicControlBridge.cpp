// Fill out your copyright notice in the Description page of Project Settings.


#include "Bridges/ControlBridges/NonDynamicBasicControlBridge.h"

void UNonDynamicBasicControlBridge::Execute(int _Slot, int _SecondarySlot, UObject* _RelevantObject, UObject* _SecondaryObject)
{
	ExecuteDelegate.ExecuteIfBound(_Slot, _SecondarySlot, _RelevantObject, _SecondaryObject);
}

void UNonDynamicBasicControlBridge::BindFunction(UObject* _FunctionOwner, FName _FunctionName) 
{
	ExecuteDelegate.BindUFunction(_FunctionOwner, _FunctionName);
}