// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/InventoryComponent.h"
#include "CharacterInventoryComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class INVENTORYSYSTEM_API UCharacterInventoryComponent : public UInventoryComponent
{
	GENERATED_BODY()

public:

	//Overriden to ensure the inventory slots are populated based on the max inventory slots
	virtual void BeginPlay() override;

private:

	//The maximum number of inventory slots that the inventory can hold
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	int MaxInventorySlots;
	
};
