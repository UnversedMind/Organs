// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryComponent.h"
#include "Bridges/PropertyBridges/StructPropertyBridge.h"
#include "Bridges/PropertyBridges/IntPropertyBridge.h"
#include "Bridges/ControlBridges/IntControlBridge.h"

UPropertyBridge* UInventoryComponent::GetData_Implementation() 
{
	TMap<FName, UPropertyBridge*> Items;
	
	for (TPair<int, int> _InventoryItem : InventoryIds) 
	{
		
		//Items.Add(FName(_InventoryItem.itemName), UIntPropertyBridge::CreatePropertyBridge(_InventoryItem.itemDescription));
	}
	UPropertyBridge* _Data = UStructPropertyBridge::CreatePropertyBridge(Items);
	return _Data;
}

void UInventoryComponent::AddItemToInventory(int _Id)
{
	if (InventoryIds.Contains(_Id)) 
	{
		InventoryIds[_Id]++;
		return;
	}
	InventoryIds.Add(_Id);
}

UControlBridge* UInventoryComponent::GetControls_Implementation()
{
	UControlBridge* _Controls = UIntControlBridge::CreateControlBridge(this, GET_FUNCTION_NAME_CHECKED_OneParam(UInventoryComponent, AddItemToInventory, int), UIntControlBridge::StaticClass());
	return _Controls;
}
