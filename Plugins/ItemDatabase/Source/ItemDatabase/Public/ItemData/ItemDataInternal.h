// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemDataInternal.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType, Blueprintable)
struct FItemDataInternal
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (GetKeyOptions = "ItemDatabase.ItemSettings.GetItemDataTypeNames"))
	TMap<FName, float> AdditionalData;
};
