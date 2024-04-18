// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryComponent.h"
#include "UI/Bridges/StructPropertyBridge.h"
#include "UI/Bridges/StringPropertyBridge.h"
#include "UI/Bridges/StructControlBridge.h"

UPropertyBridge* UInventoryComponent::GetData_Implementation() 
{
	TMap<FName, UPropertyBridge*> Items;
	TMap<FName, UPropertyBridge*> ItemDetails;
	
	for (FInventoryItem _InventoryItem : Inventory) 
	{
		Items.Add(FName(_InventoryItem.itemName), UStringPropertyBridge::CreatePropertyBridge(_InventoryItem.itemDescription));
	}
	UPropertyBridge* _Data = UStructPropertyBridge::CreatePropertyBridge(Items);
	return _Data;
}

void UInventoryComponent::AddItemToInventory(FInventoryItem _NewItem)
{
	Inventory.Add(_NewItem);
}

UControlBridge* UInventoryComponent::GetControls_Implementation()
{
	UControlBridge* _Controls = UStructControlBridge::CreateControlBridge(this, GET_FUNCTION_NAME_CHECKED_OneParam(UInventoryComponent, AddItemToInventory, FInventoryItem), UStructControlBridge::StaticClass());
	UStructControlBridge* _StructBridge = Cast<UStructControlBridge>(_Controls);
	_StructBridge->BindObject<UInventoryComponent, FInventoryItem>(this, &UInventoryComponent::AddItemToInventory);
	return _Controls;
}
