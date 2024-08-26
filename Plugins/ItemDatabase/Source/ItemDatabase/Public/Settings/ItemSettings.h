// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ItemData/ItemDataInternal.h"
#include "Functions/ItemFunctions.h"
#include "ItemSettings.generated.h"

/**
 * 
 */

UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "Item Settings"))
class ITEMDATABASE_API UItemSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	static FItemDataInternal GetItemVariablesFromType(FName _ItemType);

	static FFunctionList GetFunctionListFromType(FName _ItemType);

	UFUNCTION()
	static TArray<FName> GetItemDataTypeNames();

	UFUNCTION()
	static TArray<FName> GetItemTypes();

	UFUNCTION()
	static TArray<FName> GetItemNames();

	UFUNCTION()
	static TArray<FName> GetFunctionNames();

	UFUNCTION(BlueprintPure)
	static FItemData GetItemDataFromName(FName _ItemName);

private:

	UItemSettings();

	void LoadDataTable();

	const UDataTable* GetDataTable();

	UPROPERTY(EditAnywhere, Config, meta = (RequiredAssetDataTags = "RowStructure=/Script/ItemDatabase.ItemData", AllowPrivateAccess = "true"))
	TSoftObjectPtr<class UDataTable> ItemList;

	UPROPERTY(EditAnywhere, Config, meta = (AllowPrivateAccess = "true"))
	TArray<FName> ItemTypes;

	UPROPERTY(EditAnywhere, Config, meta = (AllowPrivateAccess = "true"))
	TArray<FName> ItemDataTypes;

	UPROPERTY(EditAnywhere, Config, meta = (AllowPrivateAccess = "true"), Category="Functions")
	TArray<FName> ItemFunctionNames;

	UPROPERTY(EditAnywhere, Config, meta = (AllowPrivateAccess = "true", GetKeyOptions = "ItemDatabase.ItemSettings.GetItemTypes"), Category="Functions")
	TMap<FName, FFunctionList> ItemTypeToDefaultFunctionList;

	UPROPERTY(EditAnywhere, Config, meta = (AllowPrivateAccess = "true", GetKeyOptions = "ItemDatabase.ItemSettings.GetItemTypes"))
	TMap<FName, FItemDataInternal> ItemTypeToDefaultVariables;

	TObjectPtr<class UDataTable> ItemListInstance;

};