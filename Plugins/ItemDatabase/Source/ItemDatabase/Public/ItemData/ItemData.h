// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData/ItemDataInternal.h"
#include "Functions/ItemFunctions.h"
#include "ItemData.generated.h"

USTRUCT(Blueprintable, BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

public:

	FItemData()
	{

	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (GetOptions = "ItemDatabase.ItemSettings.GetItemTypes"))
	FName ItemType;

	FName PreviousItemType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UTexture2D> ItemIcon;

	UPROPERTY(EditAnywhere)
	FItemDataInternal AdditionalData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FFunctionList FunctionList;

	void UpdateAdditionalDataFromItemType();

	virtual void OnDataTableChanged(const UDataTable* InDataTable, const FName InRowName) override;

};