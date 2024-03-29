// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/InteractionController.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

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

void UInteractionController::SphereTraceFromCamera(FHitResult& _HitResult, bool& _Success, TArray<TEnumAsByte<EObjectTypeQuery>> _ObjectTypes)
{
	FVector traceStartLocation = GetOwner()->GetActorLocation();
	FVector cameraLocation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetForwardVector();
	FVector traceEndLocation = traceStartLocation + (cameraLocation * 300.0f);
	UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), traceStartLocation, traceEndLocation, 60.0f, _ObjectTypes, false, TArray<AActor*>{},
		EDrawDebugTrace::None, _HitResult, true);
	_Success = _HitResult.bBlockingHit;
}

void UInteractionController::CheckForInteractableItems(FHitResult& _HitResult, bool& _Success, TArray<TEnumAsByte<EObjectTypeQuery>> _ObjectTypes)
{
	SphereTraceFromCamera(_HitResult, _Success, _ObjectTypes);

	if (!_Success) 
	{
		return;
	}

	if (!_HitResult.GetActor()) 
	{
		_Success = false;
		return;
	}

	if (!_HitResult.GetActor()->Implements<UInteraction>()) 
	{
		_Success = false;
		return;
	}

	IInteraction::Execute_CanUserInteract(_HitResult.GetActor(), _Success);
}

void UInteractionController::Interact(AActor* _InteractableItem)
{
	bool bSuccess;
	IInteraction::Execute_Interact(_InteractableItem, bSuccess);

	OnActionTriggered.Broadcast(this, _InteractableItem, bSuccess);
	if (IInteraction::Execute_IsSingleShotInteraction(_InteractableItem)) {
		return;
	}
	InteractableItem = _InteractableItem;

	float interactionTime = IInteraction::Execute_GetInteractionTime(InteractableItem.GetObject());
	if (interactionTime <= 0) 
	{
		return;
	}
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
