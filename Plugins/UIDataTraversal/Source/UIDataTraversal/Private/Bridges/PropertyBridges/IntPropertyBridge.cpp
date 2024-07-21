// Fill out your copyright notice in the Description page of Project Settings.


#include "Bridges/PropertyBridges/IntPropertyBridge.h"

UIntPropertyBridge* UIntPropertyBridge::CreatePropertyBridge(int _IntValue)
{
	UIntPropertyBridge* _NewIntPropertyBridge = UPropertyBridge::CreateBridge<UIntPropertyBridge>();
	_NewIntPropertyBridge->IntValue = _IntValue;
	return _NewIntPropertyBridge;
}