// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData/ItemDataInternal.h"
#include "Functions/FunctionListInfo.h"
#include "ItemData.generated.h"

USTRUCT(Blueprintable, BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

public:

	FItemData()
	{

	}

	//The item's name
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ItemName;

	//The item's description
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString ItemDescription;

	//The item's category
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (GetOptions = "ItemDatabase.ItemSettings.GetItemTypes"))
	FName ItemType;

	//The previous item type - this is used to prevent issues with the data table loading
	FName PreviousItemType;

	//The item's icon
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UTexture2D> ItemIcon;

	//The item's list of additional data (e.g. HP:50.0f)
	UPROPERTY(EditAnywhere)
	FItemDataInternal AdditionalData;

	//The list of functions that this item can execute
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (GetValueOptions = "FunctionDatabase.FunctionSettings.GetFunctionIdentifiers"))
	TMap<FName, FName> FunctionList;

	//The item's list of additional data per function (e.g. HP:50.0f)
	UPROPERTY(VisibleAnywhere, meta = (ReadOnlyKeys, ForceInlineRow, NoResetToDefault))
	TMap<FName, FFunctionData> AdditionalFunctionData;

	//Whether this item is loaded - used to prevent issues with the data table loading in
	bool bIsLoaded;

	//Update the AdditionalData and FunctionList from the item type
	void UpdateAdditionalDataFromItemType();

	//Populates the AdditionalFunctionData map for ease of user changing variables
	void PopulateAdditionalFunctionData();

	//On data table changed, rename the row if required, and update the AdditionalData and FunctionList from the item type
	virtual void OnDataTableChanged(const UDataTable* InDataTable, const FName InRowName) override;

};