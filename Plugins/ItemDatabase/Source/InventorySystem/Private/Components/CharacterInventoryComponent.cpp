// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CharacterInventoryComponent.h"

void UCharacterInventoryComponent::BeginPlay()
{
	ClearInventorySlots();
	for (int i = 0; i < MaxInventorySlots; i++)
	{
		AddInventorySlot();
	}
	Super::BeginPlay();
}
