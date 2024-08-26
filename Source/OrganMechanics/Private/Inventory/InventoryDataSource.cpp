// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryDataSource.h"
#include "Bridges/PropertyBridges/StructPropertyBridge.h"
#include "Bridges/PropertyBridges/IntPropertyBridge.h"
#include "Bridges/ControlBridges/IntControlBridge.h"

UPropertyBridge* UInventoryDataSource::GetData_Implementation() 
{
	TMap<FName, UPropertyBridge*> Items;
	UPropertyBridge* _Data = UStructPropertyBridge::CreatePropertyBridge(Items);
	return _Data;
}