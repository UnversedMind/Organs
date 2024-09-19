// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

//Each inventory slot has a name and a quantity - all other item info can be obtained from the ItemList via the ItemName
USTRUCT(BlueprintType, Blueprintable)
struct FInventorySlot 
{
	GENERATED_BODY()

	FInventorySlot() 
	{
		ItemName = FName();
		ItemQuantity = 0;
	}

	FInventorySlot(FName _ItemName, int _ItemQuantity)
	{
		ItemName = _ItemName;
		ItemQuantity = _ItemQuantity;
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(GetOptions = "ItemDatabase.ItemSettings.GetItemNames"))
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int ItemQuantity;
};

//The component to be added to any actor which is meant to hold items (i.e. a treasure chest, the player's inventory)
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORYSYSTEM_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	//Adds item to the provided slot
	void AddItemToInventoryAtSlot(FName _ItemName, int _SlotNumber);

	//Adds an item at the next available slot - this could be the next stackable slot for stackable items, or the next
	//empty slot for non-stackable items
	UFUNCTION(BlueprintCallable)
	void AddItemToInventoryAtNextAvailableSlot(FName _ItemName);

	//Moves item from SlotOne to SlotTwo, and item from SlotTwo to SlotOne
	UFUNCTION(BlueprintCallable)
	void SwapSlotInfo(int _SlotOne, int _SlotTwo);

	//Removes all items from the provided slot
	UFUNCTION(BlueprintCallable)
	void EmptyInventorySlot(int _SlotNumber);

	//Returns all of the inventory slots
	UFUNCTION(BlueprintPure)
	virtual TArray<FInventorySlot>& GetInventorySlots();

	//Removes one item from the provided slot
	UFUNCTION(BlueprintCallable)
	void DiscardInventoryItem(int _SlotNumber);

	//Delegate to facilitate visual updates when the inventory is updated, for example updating the UI when altering the 
	//inventory in the UI menu
	UPROPERTY(BlueprintAssignable)
	FOnInventoryUpdated OnInventoryUpdated;

	//Gets the item name from the slot number
	UFUNCTION(BlueprintPure)
	FName GetItemAtSlot(int _SlotNumber);

	//Removes all inventory slots
	void ClearInventorySlots();

	//Adds empty inventory slot
	void AddInventorySlot();

	//Overridden to allow for adding default item slots
	virtual void BeginPlay() override;

private:

	//The list of default items for this inventory to hold
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<FInventorySlot> DefaultItemSlots;

	//The list of inventory slots that this component holds
	TArray<FInventorySlot> InventorySlots;

	//Returns true if there is a slot at the provided slot number
	bool IsValidSlot(int _SlotNumber);

	//Gets the next empty inventory slot
	int GetNextEmptySlot();
		
	//Gets the next stackable slot (if the item already exists in the inventory), or the next empty slot if an item doesn't exist
	int GetNextAvailableSlotForStackableItem(FName _ItemName);

	//Gets the first slot that holds an item with the name _ItemName, after the StartingSlot
	int GetSlotFromItemName(FName _ItemName);
};
