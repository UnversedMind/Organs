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

	static bool IsStackableItem(FName _ItemName);

	UPROPERTY(EditAnywhere, Config, BlueprintReadOnly, meta = (GetOptions = "ItemDatabase.ItemSettings.GetItemNames"))
	TArray<FName> StackableItemsList;
};
