// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/InteractionController.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Controllers/InteractableItemLocator.h"

void UInteractionController::HandleInteraction(AActor* _InteractableItem)
{
	if (InteractableItem.GetObject()) 
	{
		if (!GetOwner()->GetWorldTimerManager().IsTimerActive(Timer))
		{
			StopInteract();
		}
		return;
	}
	Interact(_InteractableItem);
}

AActor* UInteractionController::GetItemFromItemLocator(bool& _Success)
{
	if (!ItemLocator) 
	{
		_Success = false;
		return nullptr;
	}
	return ItemLocator->GetInteractableItem(_Success);
}

void UInteractionController::Interact(AActor* _InteractableItem)
{
	bool bSuccess;
	IInteraction::Execute_Interact(_InteractableItem, bSuccess);

	OnActionTriggered.Broadcast(this, _InteractableItem, bSuccess);
	if (IInteraction::Execute_IsSingleShotInteraction(_InteractableItem)) 
	{
		IInteraction::Execute_PostInteract(_InteractableItem);
		return;
	}
	InteractableItem = _InteractableItem;

	float interactionTime = IInteraction::Execute_GetInteractionTime(InteractableItem.GetObject());
	if (interactionTime <= 0) 
	{
		return;
	}
	IInteraction::Execute_PostInteract(_InteractableItem);
	HandleAutomaticInteraction();
}

void UInteractionController::StopInteract()
{
	if (!InteractableItem.GetObject()) 
	{
		return;
	}

	bool bSuccess;
	Timer.Invalidate();
	IInteraction::Execute_StopInteract(InteractableItem.GetObject(), bSuccess);
	OnStopActionTriggered.Broadcast(this, InteractableItem.GetObject(), bSuccess);
	IInteraction::Execute_PostStopInteract(InteractableItem.GetObject());
	InteractableItem = nullptr;
}

UObject* UInteractionController::GetInteractableItem()
{
	return InteractableItem.GetObject();
}

void UInteractionController::HandleAutomaticInteraction()
{
	float timeDelay = InteractableItem->GetInteractionTime_Implementation();
	GetOwner()->GetWorldTimerManager().SetTimer(Timer, this, &UInteractionController::StopInteract, timeDelay, false);
}
