// Fill out your copyright notice in the Description page of Project Settings.


#include "Bridges/PropertyBridges/StringPropertyBridge.h"

UStringPropertyBridge* UStringPropertyBridge::CreatePropertyBridge(FString _StringValue)
{
	UStringPropertyBridge* _NewStringPropertyBridge = UPropertyBridge::CreateBridge<UStringPropertyBridge>();
	_NewStringPropertyBridge->StringValue = _StringValue;
	return _NewStringPropertyBridge;
}
