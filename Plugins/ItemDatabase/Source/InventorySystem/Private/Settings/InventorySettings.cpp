// Fill out your copyright notice in the Description page of Project Settings.


#include "Settings/InventorySettings.h"
#include "Settings/ItemSettings.h"

bool UInventorySettings::IsStackableItem(FName _ItemName)
{
	UInventorySettings* inventorySettings = const_cast<UInventorySettings*>(GetDefault<UInventorySettings>());

	if (inventorySettings->StackableItemsList.Contains(_ItemName)) 
	{
		return true;
	}
	return false;
}
