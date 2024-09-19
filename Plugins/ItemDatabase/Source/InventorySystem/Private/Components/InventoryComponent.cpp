// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"
#include "Settings/InventorySettings.h"

void UInventoryComponent::AddItemToInventoryAtSlot(FName _ItemName, int _SlotNumber)
{
	if (!IsValidSlot(_SlotNumber)) 
	{
		return;
	}
	TArray<FInventorySlot>& inventorySlots = GetInventorySlots();

	inventorySlots[_SlotNumber].ItemName = _ItemName;
	inventorySlots[_SlotNumber].ItemQuantity += 1;
	OnInventoryUpdated.Broadcast();
}

void UInventoryComponent::AddItemToInventoryAtNextAvailableSlot(FName _ItemName)
{
	int nextAvailableSlot = -1;
	if (UInventorySettings::IsStackableItem(_ItemName)) 
	{
		nextAvailableSlot = GetNextAvailableSlotForStackableItem(_ItemName);
		AddItemToInventoryAtSlot(_ItemName, nextAvailableSlot);
		return;
	}
	nextAvailableSlot = GetNextEmptySlot();
	AddItemToInventoryAtSlot(_ItemName, nextAvailableSlot);
}

void UInventoryComponent::SwapSlotInfo(int _SlotOne, int _SlotTwo)
{
	if (!IsValidSlot(_SlotOne) || !IsValidSlot(_SlotTwo)) 
	{
		return;
	}

	TArray<FInventorySlot>& inventorySlots = GetInventorySlots();

	FInventorySlot slotInfoOne = inventorySlots[_SlotOne];
	FInventorySlot slotInfoTwo = inventorySlots[_SlotTwo];
	
	inventorySlots[_SlotOne] = slotInfoOne;
	inventorySlots[_SlotTwo] = slotInfoTwo;
	OnInventoryUpdated.Broadcast();
}

void UInventoryComponent::EmptyInventorySlot(int _SlotNumber)
{
	TArray<FInventorySlot>& inventorySlots = GetInventorySlots();
	inventorySlots[_SlotNumber] = FInventorySlot();
}

TArray<FInventorySlot>& UInventoryComponent::GetInventorySlots()
{
	return InventorySlots;
}

void UInventoryComponent::DiscardInventoryItem(int _SlotNumber)
{
	if (!IsValidSlot(_SlotNumber))
	{
		return;
	}

	TArray<FInventorySlot>& inventorySlots = GetInventorySlots();

	inventorySlots[_SlotNumber].ItemQuantity -= 1;

	if (inventorySlots[_SlotNumber].ItemQuantity <= 0)
	{
		EmptyInventorySlot(_SlotNumber);
	}
	OnInventoryUpdated.Broadcast();
}

FName UInventoryComponent::GetItemAtSlot(int _SlotNumber)
{
	TArray<FInventorySlot>& inventorySlots = GetInventorySlots();
	if (!inventorySlots.IsValidIndex(_SlotNumber))
	{
		return FName();
	}
	return inventorySlots[_SlotNumber].ItemName;
}

void UInventoryComponent::ClearInventorySlots()
{
	TArray<FInventorySlot>& inventorySlots = GetInventorySlots();
	inventorySlots.Empty();
}

void UInventoryComponent::AddInventorySlot()
{
	TArray<FInventorySlot>& inventorySlots = GetInventorySlots();
	inventorySlots.Add(FInventorySlot());
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	for (int i = 0; i < DefaultItemSlots.Num(); i++)
	{
		if (!IsValidSlot(i))
		{
			AddInventorySlot();
		}
		for (int a = 0; a < DefaultItemSlots[i].ItemQuantity; a++) 
		{
			if (!IsValidSlot(i + a))
			{
				AddInventorySlot();
			}
			AddItemToInventoryAtNextAvailableSlot(DefaultItemSlots[i].ItemName);
		}
	}
}

bool UInventoryComponent::IsValidSlot(int _SlotNumber)
{
	TArray<FInventorySlot>& inventorySlots = GetInventorySlots();
	return inventorySlots.IsValidIndex(_SlotNumber);
}

int UInventoryComponent::GetNextEmptySlot()
{
	return GetSlotFromItemName(FName());
}

int UInventoryComponent::GetNextAvailableSlotForStackableItem(FName _ItemName)
{
	int slotNumber = GetSlotFromItemName(_ItemName);
	if (!IsValidSlot(slotNumber))
	{
		slotNumber = GetNextEmptySlot();
	}
	return slotNumber;
}

int UInventoryComponent::GetSlotFromItemName(FName _ItemName)
{
	int slotIndex = -1;
	TArray<FInventorySlot>& inventorySlots = GetInventorySlots();
	for (int i = 0; i < inventorySlots.Num(); i++) 
	{
		if (inventorySlots[i].ItemName == _ItemName)
		{
			if (inventorySlots[i].ItemQuantity < UInventorySettings::GetStackLimit(_ItemName)) 
			{
				slotIndex = i;
				break;
			}
		}
	}
	return slotIndex;
}
