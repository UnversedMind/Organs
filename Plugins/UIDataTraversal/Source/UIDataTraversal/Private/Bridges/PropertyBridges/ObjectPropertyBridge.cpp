// Fill out your copyright notice in the Description page of Project Settings.


#include "Bridges/PropertyBridges/ObjectPropertyBridge.h"

UObjectPropertyBridge* UObjectPropertyBridge::CreatePropertyBridge(UObject* _ObjectValue)
{
	UObjectPropertyBridge* _NewObjectPropertyBridge = UPropertyBridge::CreateBridge<UObjectPropertyBridge>();
	_NewObjectPropertyBridge->ObjectValue = _ObjectValue;
	return _NewObjectPropertyBridge;
}