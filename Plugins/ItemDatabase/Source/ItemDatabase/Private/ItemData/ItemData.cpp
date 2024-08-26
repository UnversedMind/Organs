// Copyright Epic Games, Inc. All Rights Reserved.

#include "ItemData/ItemData.h"
#include "Settings/ItemSettings.h"
#include "DataTableEditorUtils.h"

void FItemData::UpdateAdditionalDataFromItemType() 
{
	if (PreviousItemType == FName() && ItemType != FName())
	{
		PreviousItemType = ItemType;
		return;
	}
	if (PreviousItemType == ItemType)
	{
		return;
	}
	FItemDataInternal internalData = UItemSettings::GetItemVariablesFromType(ItemType);
	FFunctionList functionList = UItemSettings::GetFunctionListFromType(ItemType);
	AdditionalData = internalData;
	FunctionList = functionList;
	PreviousItemType = ItemType;
}

void FItemData::OnDataTableChanged(const UDataTable* InDataTable, const FName InRowName)
{
#if WITH_EDITOR
	UpdateAdditionalDataFromItemType();
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
