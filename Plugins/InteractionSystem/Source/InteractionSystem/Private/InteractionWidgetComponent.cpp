// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionWidgetComponent.h"
#include "Controllers/InteractionController.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

void UInteractionWidgetComponent::BeginPlay()
{
	Super::BeginPlay();
	InteractionController = GetOwner()->GetComponentByClass<UInteractionController>();
}

void UInteractionWidgetComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!InteractionController) 
	{
		return;
	}

	if (InteractionController->GetInteractableItem()) 
	{
		SetVisibility(false);
		return;
	}

	bool bSuccess = false;
	TObjectPtr<AActor> relevantActor = InteractionController->GetItemFromItemLocator(bSuccess);
	if (bSuccess) 
	{
		FVector newLocation = relevantActor->GetActorLocation() + Offset;
		FVector cameraLocation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation();
		FRotator newRotation = UKismetMathLibrary::FindLookAtRotation(newLocation, cameraLocation);

		SetWorldLocationAndRotation(newLocation, newRotation);
	}
	SetVisibility(bSuccess);
}