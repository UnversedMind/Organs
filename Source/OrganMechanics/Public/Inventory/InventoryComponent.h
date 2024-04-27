// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UI/DataModelInterface.h"
#include "InventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FInventoryItem 
{
	GENERATED_BODY()

	FInventoryItem() 
	{

	}

	FInventoryItem(FString _Name, FString _Description) 
	{
		itemName = _Name;
		itemDescription = _Description;
	}

	UPROPERTY(BlueprintReadWrite)
	FString itemName;
	UPROPERTY(BlueprintReadWrite)
	FString itemDescription;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ORGANMECHANICS_API UInventoryComponent : public UActorComponent, public IDataModelInterface
{
	GENERATED_BODY()

public:

	virtual class UPropertyBridge* GetData_Implementation() override;

	virtual class UControlBridge* GetControls_Implementation() override;

	void AddItemToInventory(int _Id);

private:

	TMap<int, int> InventoryIds;
		
};
