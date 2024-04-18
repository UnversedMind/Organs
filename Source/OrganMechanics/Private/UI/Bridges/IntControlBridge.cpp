#include "UI/Bridges/IntControlBridge.h"

void UIntControlBridge::UpdateValue(int _NewValue)
{
	UpdateValueDelegate.ExecuteIfBound(_NewValue);
}

void UIntControlBridge::BindFunction(UObject* _FunctionOwner, FName _FunctionName)
{
	UpdateValueDelegate.BindUFunction(_FunctionOwner, _FunctionName);
}
