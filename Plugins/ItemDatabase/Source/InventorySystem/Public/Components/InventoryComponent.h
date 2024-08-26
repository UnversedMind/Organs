// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

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

	UPROPERTY(BlueprintReadWrite)
	FName ItemName;

	UPROPERTY(BlueprintReadWrite)
	int ItemQuantity;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORYSYSTEM_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	void AddItemToInventoryAtSlot(FName _ItemName, int _SlotNumber);

	UFUNCTION(BlueprintCallable)
	void AddItemToInventoryAtNextAvailableSlot(FName _ItemName);

	UFUNCTION(BlueprintCallable)
	void SwapSlotInfo(int _SlotOne, int _SlotTwo);

	UFUNCTION(BlueprintCallable)
	void EmptyInventorySlot(int _SlotNumber);

	UFUNCTION(BlueprintPure)
	TArray<FInventorySlot> GetInventorySlots();

	UFUNCTION(BlueprintCallable)
	void UseInventoryItem(int _SlotNumber);

	UFUNCTION(BlueprintCallable)
	void ExamineInventoryItem(int _ItemID);

	UFUNCTION(BlueprintCallable)
	void DiscardInventoryItem(int _SlotNumber);

	UPROPERTY(BlueprintAssignable)
	FOnInventoryUpdated OnInventoryUpdated;

	UFUNCTION(BlueprintPure)
	FName GetItemAtSlot(int _SlotNumber);

private:

	TArray<FInventorySlot> InventorySlots;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess = "true"))
	int MaxInventorySlots;

	bool IsValidSlot(int _SlotNumber);

	int GetNextEmptySlot();
		
	int GetNextAvailableSlotForStackableItem(FName _ItemName);

	int GetSlotFromItemName(FName _ItemName);
};
