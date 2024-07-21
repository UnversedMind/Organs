// Fill out your copyright notice in the Description page of Project Settings.


#include "Bridges/ControlBridges/MultiControlBridge.h"

void UMultiControlBridge::BindFunction(UObject* _FunctionOwner, FName _FunctionName)
{
	OnControlExecutionCompleted.BindUFunction(_FunctionOwner, _FunctionName);
}

UControlBridge* UMultiControlBridge::GetBridgeFromIndex(int index)
{
	check(Controls.IsValidIndex(index));
	return Controls[index];
}

void UMultiControlBridge::CompleteControlExecution()
{
	if (OnControlExecutionCompleted.IsBound()) 
	{
		OnControlExecutionCompleted.Execute();
	}
}
