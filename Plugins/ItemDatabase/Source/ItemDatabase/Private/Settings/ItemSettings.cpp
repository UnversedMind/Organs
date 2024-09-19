// Fill out your copyright notice in the Description page of Project Settings.


#include "Settings/ItemSettings.h"
#include "Settings/FunctionSettings.h"
#include "Functions/FunctionInfo.h"
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
	const UDataTable* dataTable = itemSettings->GetItemDataTable();

	if (!dataTable) 
	{
		return itemNames;
	}

	itemNames = dataTable->GetRowNames();
	return itemNames;
}

FItemData UItemSettings::GetItemDataFromName(FName _ItemName)
{
	UItemSettings* itemSettings = const_cast<UItemSettings*>(GetDefault<UItemSettings>());
	UDataTable* dataTable = const_cast<UDataTable*>(itemSettings->GetItemDataTable());

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

FFunctionInfo UItemSettings::GetFunctionInfoFromIdentifierRelevantToItem(FName _FunctionIdentifier, FItemData _ItemData, FName& _FunctionName)
{
	if (!_ItemData.FunctionList.Contains(_FunctionIdentifier)) 
	{
		return FFunctionInfo();
	}
	_FunctionName = _ItemData.FunctionList[_FunctionIdentifier];

	FFunctionInfo functionInfo = UFunctionSettings::GetFunctionInfoFromIdentifier(_FunctionIdentifier);
	functionInfo.PopulateConditionalInfo(_ItemData.AdditionalFunctionData[_FunctionIdentifier].ConditionalData);
	functionInfo.PopulateExecutableInfo(_ItemData.AdditionalFunctionData[_FunctionIdentifier].ExecutableData);
	return functionInfo;
}

UItemSettings::UItemSettings()
{
	LoadItemDataTable();
}

void UItemSettings::LoadItemDataTable()
{
	ItemListInstance = ItemList.LoadSynchronous();
}

const UDataTable* UItemSettings::GetItemDataTable()
{
	if (!ItemListInstance) 
	{
		LoadItemDataTable();
	}
	return ItemListInstance;
}
