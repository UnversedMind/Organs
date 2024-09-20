// Copyright Epic Games, Inc. All Rights Reserved.

#include "ItemData/ItemData.h"
#include "Settings/ItemSettings.h"
#include "Settings/FunctionSettings.h"
#include "Functions/FunctionInfo.h"
#include "DataTableEditorUtils.h"

void FItemData::UpdateAdditionalDataFromItemType() 
{
	if (PreviousItemType == FName() && ItemType != FName())
	{
		if (bIsLoaded)
		{
			PreviousItemType = ItemType;
			return;
		}
	}

	if (PreviousItemType == ItemType)
	{
		return;
	}

	bIsLoaded = true;
	
	FItemDataInternal internalData = UItemSettings::GetItemVariablesFromType(ItemType);
	AdditionalData = internalData;
	PreviousItemType = ItemType;
}

void FItemData::PopulateAdditionalFunctionData()
{
	TArray<FName> functionIdentifiers;
	FunctionList.GenerateKeyArray(functionIdentifiers);
	if (!functionIdentifiers.IsValidIndex(0)) 
	{
		AdditionalFunctionData.Empty();
		return;
	}

	for (FName functionInfo : functionIdentifiers)
	{
		TArray<FName> additionalDataNames;
		AdditionalFunctionData.GenerateKeyArray(additionalDataNames);

		for (FName additionalDataName : additionalDataNames) 
		{
			if (!functionIdentifiers.Contains(additionalDataName))
			{
				AdditionalFunctionData.Remove(additionalDataName);
			}
		}

		if (AdditionalFunctionData.Contains(functionInfo)) 
		{
			continue;
		}

		FFunctionInfo functionInfoItem = UFunctionSettings::GetFunctionInfoFromIdentifier(functionInfo);
		FFunctionData functionDataItem = FFunctionData(functionInfoItem.FunctionConditions.Functions, functionInfoItem.FunctionExecutions.Functions);
		AdditionalFunctionData.Add(functionInfo, functionDataItem);
	}
}

void FItemData::OnDataTableChanged(const UDataTable* InDataTable, const FName InRowName)
{
#if WITH_EDITOR
	UpdateAdditionalDataFromItemType();
	PopulateAdditionalFunctionData();
	UDataTable* dataTable = const_cast<UDataTable*>(InDataTable);
	if (this == InDataTable->FindRow<FItemData>(InRowName, FString()))
	{
		if (InRowName != ItemName)
		{
			FDataTableEditorUtils::RenameRow(dataTable, InRowName, ItemName);
		}
	}
#endif
}
