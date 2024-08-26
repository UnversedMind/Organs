// Fill out your copyright notice in the Description page of Project Settings.


#include "Settings/ItemSettings.h"
#include "ItemData/ItemData.h"

FItemDataInternal UItemSettings::GetItemVariablesFromType(FName _ItemType)
{
	const UItemSettings* itemSettings = GetDefault<UItemSettings>();

	if (!itemSettings->ItemTypeToDefaultVariables.Contains(_ItemType))
	{
		return FItemDataInternal();
	}
	return itemSettings->ItemTypeToDefaultVariables[_ItemType];
}

FFunctionList UItemSettings::GetFunctionListFromType(FName _ItemType)
{
	const UItemSettings* itemSettings = GetDefault<UItemSettings>();

	if (!itemSettings->ItemTypeToDefaultFunctionList.Contains(_ItemType))
	{
		return FFunctionList();
	}
	return itemSettings->ItemTypeToDefaultFunctionList[_ItemType];
}

TArray<FName> UItemSettings::GetItemDataTypeNames()
{
	const UItemSettings* itemSettings = GetDefault<UItemSettings>();
	return itemSettings->ItemDataTypes;
}

TArray<FName> UItemSettings::GetItemTypes()
{
	const UItemSettings* itemSettings = GetDefault<UItemSettings>();
	return itemSettings->ItemTypes;
}

TArray<FName> UItemSettings::GetItemNames()
{
	TArray<FName> itemNames;

	UItemSettings* itemSettings = const_cast<UItemSettings*>(GetDefault<UItemSettings>());
	const UDataTable* dataTable = itemSettings->GetDataTable();

	if (!dataTable) 
	{
		return itemNames;
	}

	itemNames = dataTable->GetRowNames();
	return itemNames;
}

TArray<FName> UItemSettings::GetFunctionNames()
{
	UItemSettings* itemSettings = const_cast<UItemSettings*>(GetDefault<UItemSettings>());

	return itemSettings->ItemFunctionNames;
}

FItemData UItemSettings::GetItemDataFromName(FName _ItemName)
{
	UItemSettings* itemSettings = const_cast<UItemSettings*>(GetDefault<UItemSettings>());
	UDataTable* dataTable = const_cast<UDataTable*>(itemSettings->GetDataTable());

	if (!dataTable)
	{
		return FItemData();
	}

	if (!dataTable->GetRowNames().Contains(_ItemName)) 
	{
		return FItemData();
	}
	FItemData itemData = FItemData();
	itemData = *dataTable->FindRow<FItemData>(_ItemName, FString());
	return itemData;
}

UItemSettings::UItemSettings()
{
	LoadDataTable();
}

void UItemSettings::LoadDataTable()
{
	ItemListInstance = ItemList.LoadSynchronous();
}

const UDataTable* UItemSettings::GetDataTable()
{
	if (!ItemListInstance) 
	{
		LoadDataTable();
	}
	return ItemListInstance;
}
