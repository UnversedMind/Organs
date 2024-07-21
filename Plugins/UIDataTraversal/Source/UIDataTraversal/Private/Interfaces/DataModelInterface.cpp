// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/DataModelInterface.h"

// Add default functionality here for any IDataModelInterface functions that are not pure virtual.

UPropertyBridge* IDataModelInterface::GetData_Implementation()
{
	return nullptr;
}

UControlBridge* IDataModelInterface::GetControls_Implementation()
{
	return nullptr;
}
