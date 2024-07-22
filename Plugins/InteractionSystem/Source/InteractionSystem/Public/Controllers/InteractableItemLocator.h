// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InteractableItemLocator.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew)
class INTERACTIONSYSTEM_API UInteractableItemLocator : public UObject
{
	GENERATED_BODY()

public:

	UInteractableItemLocator();

	//Checks for interactable items via sphere trace
	UFUNCTION(BlueprintCallable)
	virtual AActor* GetInteractableItem(bool& _Success);

protected:

	AActor* GetOwningActor();

private:

	TObjectPtr<AActor> OwningActor;
	
};
