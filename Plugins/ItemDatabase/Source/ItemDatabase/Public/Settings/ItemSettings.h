// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ItemSettings.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum EItemType
{
	None,
	Blade,
	Gun,
	Armour,
	MAX
};

USTRUCT(BlueprintType, Blueprintable)
struct FItemDataInternal
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (GetKeyOptions = "ItemDatabase.ItemSettings.GetItemDataTypeNames"))
	TMap<FName, float> AdditionalData;
};

UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "Item Settings"))
class ITEMDATABASE_API UItemSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	static FItemDataInternal GetItemVariablesFromType(EItemType _ItemType);

	UFUNCTION()
	static TArray<FName> GetItemDataTypeNames();

private:

	UItemSettings();

	UPROPERTY(EditAnywhere, Config, meta= (RequiredAssetDataTags = "RowStructure=/Script/ItemDatabase.ItemData", AllowPrivateAccess="true"))
	TSoftObjectPtr<class UDataTable> ItemList;

	UPROPERTY(EditAnywhere, Config, meta=(AllowPrivateAccess="true"))
	TArray<FName> ItemDataTypes;

	UPROPERTY(EditAnywhere, Config, meta = (AllowPrivateAccess = "true"))
	TMap<TEnumAsByte<EItemType>, FItemDataInternal> ItemTypeToDefaultVariables;

	TObjectPtr<class UDataTable> ItemListInstance;
};

USTRUCT(Blueprintable, BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EItemType> ItemType;

	TEnumAsByte<EItemType> PreviousItemType = EItemType::MAX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UTexture2D> ItemIcon;

	UPROPERTY(EditAnywhere)
	FItemDataInternal AdditionalData;

	virtual void OnDataTableChanged(const UDataTable* InDataTable, const FName InRowName) override
	{
#if WITH_EDITOR
		if (PreviousItemType == EItemType::MAX) 
		{
			PreviousItemType = ItemType;
			return;
		}
		if (PreviousItemType == ItemType) 
		{
			return;
		}
		FItemDataInternal internalData = UItemSettings::GetItemVariablesFromType(ItemType);
		AdditionalData = internalData;
		PreviousItemType = ItemType;
#endif
	};
};