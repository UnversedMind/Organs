// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveManagerSubsystem.h"

FName USaveManagerSubsystem::GetSaveSlotName()
{
	return SlotName;
}

void USaveManagerSubsystem::SetSaveSlotName(FName _SlotName)
{
	SlotName = _SlotName;
}