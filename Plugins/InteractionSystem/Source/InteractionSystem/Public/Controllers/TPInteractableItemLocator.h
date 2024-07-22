// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controllers/InteractableItemLocator.h"
#include "TPInteractableItemLocator.generated.h"

/**
 * 
 */
UCLASS()
class INTERACTIONSYSTEM_API UTPInteractableItemLocator : public UInteractableItemLocator
{
	GENERATED_BODY()

public:

	virtual AActor* GetInteractableItem(bool& _Success) override;

	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;

	UPROPERTY(EditAnywhere)
	float TraceDistance = 300.0f;

private:

	void SphereTraceFromCamera(FHitResult& _HitResult, bool& _Success);
	
};
