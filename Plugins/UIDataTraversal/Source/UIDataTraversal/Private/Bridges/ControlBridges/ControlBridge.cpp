// Fill out your copyright notice in the Description page of Project Settings.


#include "Bridges/ControlBridges/ControlBridge.h"

UControlBridge* UControlBridge::GetAs(TSubclassOf<UControlBridge> _Class, bool& _Success)
{
	_Success = this->GetClass()->IsChildOf(_Class);
	return this;
}

UControlBridge* UControlBridge::CreateControlBridge(UObject* _FunctionOwner, FName _FunctionName, TSubclassOf<UControlBridge> _ChildType)
{
	UControlBridge* _NewBridge = UBridge::CreateNewBridge<UControlBridge>(_FunctionOwner, _ChildType);
	_NewBridge->BindFunction(_FunctionOwner, _FunctionName);
	return _NewBridge;
}

void UControlBridge::BindFunction(UObject* _FunctionOwner, FName _FunctionName)
{
}
