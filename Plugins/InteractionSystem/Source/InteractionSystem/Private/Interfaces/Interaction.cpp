// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/Interaction.h"

// Add default functionality here for any IInteraction functions that are not pure virtual.

void IInteraction::CanUserInteract_Implementation(bool& _Success)
{
	_Success = true;
}

void IInteraction::Interact_Implementation(bool& _Success)
{
	_Success = true;
}

void IInteraction::PostInteract_Implementation()
{
}

void IInteraction::StopInteract_Implementation(bool& _Success)
{
	_Success = true;
}

void IInteraction::PostStopInteract_Implementation()
{
}

bool IInteraction::IsSingleShotInteraction_Implementation()
{
	return true;
}

float IInteraction::GetInteractionTime_Implementation()
{
	return 0.0f;
}
