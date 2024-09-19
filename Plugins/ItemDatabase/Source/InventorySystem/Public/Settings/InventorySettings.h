// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "InventorySettings.generated.h"

/**
 * 
 */
UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "Inventory Settings"))
class INVENTORYSYSTEM_API UInventorySettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	// Returns if the item is a stackable item
	static bool IsStackableItem(FName _ItemName);

	static int GetStackLimit(FName _ItemName);

	// A list of items which can be stacked, and the amount they can be stacked up to
	UPROPERTY(EditAnywhere, Config, BlueprintReadOnly, meta = (GetKeyOptions = "ItemDatabase.ItemSettings.GetItemNames"))
	TMap<FName, int> StackableItemsList;
};
