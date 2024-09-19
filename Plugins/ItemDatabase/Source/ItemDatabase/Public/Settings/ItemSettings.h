// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ItemData/ItemDataInternal.h"
#include "Functions/FunctionListInfo.h"
#include "ItemSettings.generated.h"

/**
 * 
 */

UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "Item Settings"))
class ITEMDATABASE_API UItemSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	//Returns the default Variables list from the item type provided
	static FItemDataInternal GetItemVariablesFromType(FName _ItemType);

	//Returns the list of item data types found in the ItemSettings
	UFUNCTION()
	static TArray<FName> GetItemDataTypeNames();

	//Returns the list of item types found in the ItemSettings
	UFUNCTION()
	static TArray<FName> GetItemTypes();

	//Returns the list of item names found in the item data table
	UFUNCTION()
	static TArray<FName> GetItemNames();

	//Returns the FItemData found in the data table that's associated with the ItemName
	UFUNCTION(BlueprintPure)
	static FItemData GetItemDataFromName(FName _ItemName);

	UFUNCTION(BlueprintPure)
	static FFunctionInfo GetFunctionInfoFromIdentifierRelevantToItem(FName _FunctionIdentifier, FItemData _ItemData, FName& _FunctionName);

private:

	//Loads the item data table
	UItemSettings();

	//The function that loads the item data table
	void LoadItemDataTable();

	//Returns the item data table
	const UDataTable* GetItemDataTable();

	//The soft object ptr to the item data table
	UPROPERTY(EditAnywhere, Config, meta = (RequiredAssetDataTags = "RowStructure=/Script/ItemDatabase.ItemData", AllowPrivateAccess = "true"))
	TSoftObjectPtr<class UDataTable> ItemList;

	//The list of item categories
	UPROPERTY(EditAnywhere, Config, meta = (AllowPrivateAccess = "true"))
	TArray<FName> ItemTypes;

	//The list of item variables
	UPROPERTY(EditAnywhere, Config, meta = (AllowPrivateAccess = "true"))
	TArray<FName> ItemDataTypes;

	//A map of item categories to a default value list
	UPROPERTY(EditAnywhere, Config, meta = (AllowPrivateAccess = "true", GetKeyOptions = "ItemDatabase.ItemSettings.GetItemTypes"))
	TMap<FName, FItemDataInternal> ItemTypeToDefaultVariables;

	//The object ptr to the item data table
	TObjectPtr<class UDataTable> ItemListInstance;

};