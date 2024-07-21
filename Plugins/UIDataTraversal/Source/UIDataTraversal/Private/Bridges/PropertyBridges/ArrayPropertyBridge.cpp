// Fill out your copyright notice in the Description page of Project Settings.


#include "Bridges/PropertyBridges/ArrayPropertyBridge.h"

UArrayPropertyBridge* UArrayPropertyBridge::CreatePropertyBridge(TArray<UPropertyBridge*> _Data)
{
	UArrayPropertyBridge* _NewArrayPropertyBridge = UPropertyBridge::CreateBridge<UArrayPropertyBridge>();
	_NewArrayPropertyBridge->Data = _Data;
	return _NewArrayPropertyBridge;
}

UPropertyBridge* UArrayPropertyBridge::GetBridgeFromIndex(int index) 
{
	check(Data.IsValidIndex(index));
	return Data[index];
}