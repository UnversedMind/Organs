// Fill out your copyright notice in the Description page of Project Settings.


#include "Settings/ItemSettings.h"

FItemDataInternal UItemSettings::GetItemVariablesFromType(EItemType _ItemType)
{
	const UItemSettings* itemSettings = GetDefault<UItemSettings>();

	if (!itemSettings->ItemTypeToDefaultVariables.Contains(_ItemType))
	{
		return FItemDataInternal();
	}
	return itemSettings->ItemTypeToDefaultVariables[_ItemType];
}

TArray<FName> UItemSettings::GetItemDataTypeNames()
{
	const UItemSettings* itemSettings = GetDefault<UItemSettings>();
	return itemSettings->ItemDataTypes;
}

UItemSettings::UItemSettings()
{
	ItemListInstance = ItemList.LoadSynchronous();
}