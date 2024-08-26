// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"
#include "Settings/InventorySettings.h"

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	InventorySlots.Empty();
	for (int i = 0; i < MaxInventorySlots; i++) 
	{
		InventorySlots.Add(FInventorySlot());
	}
}

void UInventoryComponent::AddItemToInventoryAtSlot(FName _ItemName, int _SlotNumber)
{
	if (!IsValidSlot(_SlotNumber)) 
	{
		return;
	}
	InventorySlots[_SlotNumber].ItemName = _ItemName;
	InventorySlots[_SlotNumber].ItemQuantity += 1;
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

	FInventorySlot slotInfoOne = InventorySlots[_SlotOne];
	FInventorySlot slotInfoTwo = InventorySlots[_SlotTwo];
	
	InventorySlots[_SlotOne] = slotInfoOne;
	InventorySlots[_SlotTwo] = slotInfoTwo;
	OnInventoryUpdated.Broadcast();
}

void UInventoryComponent::EmptyInventorySlot(int _SlotNumber)
{
	InventorySlots[_SlotNumber] = FInventorySlot();
}

TArray<FInventorySlot> UInventoryComponent::GetInventorySlots()
{
	return InventorySlots;
}

void UInventoryComponent::UseInventoryItem(int _SlotNumber)
{

}

void UInventoryComponent::ExamineInventoryItem(int _ItemID)
{
	
}

void UInventoryComponent::DiscardInventoryItem(int _SlotNumber)
{
	if (!IsValidSlot(_SlotNumber))
	{
		return;
	}

	InventorySlots[_SlotNumber].ItemQuantity -= 1;

	if (InventorySlots[_SlotNumber].ItemQuantity <= 0)
	{
		EmptyInventorySlot(_SlotNumber);
	}
	OnInventoryUpdated.Broadcast();
}

FName UInventoryComponent::GetItemAtSlot(int _SlotNumber)
{
	if (!InventorySlots.IsValidIndex(_SlotNumber)) 
	{
		return FName();
	}
	return InventorySlots[_SlotNumber].ItemName;
}

bool UInventoryComponent::IsValidSlot(int _SlotNumber)
{
	return InventorySlots.IsValidIndex(_SlotNumber);
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
	for (int i = 0; i < InventorySlots.Num(); i++) 
	{
		if (InventorySlots[i].ItemName == _ItemName)
		{
			slotIndex = i;
			break;
		}
	}
	return slotIndex;
}
