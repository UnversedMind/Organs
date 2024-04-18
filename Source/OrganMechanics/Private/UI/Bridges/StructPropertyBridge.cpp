// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Bridges/StructPropertyBridge.h"

UStructPropertyBridge* UStructPropertyBridge::CreatePropertyBridge(TMap<FName, UPropertyBridge*> _Data)
{
	UStructPropertyBridge* _NewStructPropertyBridge = UPropertyBridge::CreateBridge<UStructPropertyBridge>();
	_NewStructPropertyBridge->Data = _Data;
	return _NewStructPropertyBridge;
}

UPropertyBridge* UStructPropertyBridge::GetDataFromNameAs(FName _Name, TSubclassOf<UPropertyBridge> _Class)
{
	return Data[_Name];
}