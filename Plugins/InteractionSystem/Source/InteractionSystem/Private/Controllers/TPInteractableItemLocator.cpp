// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/TPInteractableItemLocator.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/Interaction.h"

void UTPInteractableItemLocator::SphereTraceFromCamera(FHitResult& _HitResult, bool& _Success)
{
	FVector traceStartLocation = GetOwningActor()->GetActorLocation();
	FVector cameraLocation = UGameplayStatics::GetPlayerCameraManager(GetOwningActor()->GetWorld(), 0)->GetTransformComponent()->GetForwardVector();
	FVector traceEndLocation = traceStartLocation + (cameraLocation * TraceDistance);
	UKismetSystemLibrary::SphereTraceSingleForObjects(GetOwningActor()->GetWorld(), traceStartLocation, traceEndLocation, 60.0f, ObjectTypes, false, TArray<AActor*>{},
		EDrawDebugTrace::None, _HitResult, true);
	_Success = _HitResult.bBlockingHit;
}

AActor* UTPInteractableItemLocator::GetInteractableItem(bool& _Success)
{
	FHitResult hitResult;

	SphereTraceFromCamera(hitResult, _Success);

	if (!_Success)
	{
		return nullptr;
	}

	if (!hitResult.GetActor() || !hitResult.GetActor()->Implements<UInteraction>())
	{
		_Success = false;
		return nullptr;
	}

	IInteraction::Execute_CanUserInteract(hitResult.GetActor(), _Success);

	if (!_Success)
	{
		return nullptr;
	}

	return hitResult.GetActor();
}