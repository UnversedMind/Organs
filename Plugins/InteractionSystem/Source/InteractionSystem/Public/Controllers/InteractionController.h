// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/Interaction.h"
#include "InteractionController.generated.h"

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnActionPerformed, UInteractionController*, UObject*, bool);

/**
 * This class is designed to facilitate and simplify interactions
 */
UCLASS(ClassGroup=(Controllers),meta=(BlueprintSpawnableComponent))
class INTERACTIONSYSTEM_API UInteractionController : public UActorComponent
{
	GENERATED_BODY()

public:

#pragma region Functions

	//Handles interacting or preventing an interaction as required
	UFUNCTION(BlueprintCallable)
	void HandleInteraction(AActor* _InteractableItem);

	UFUNCTION(BlueprintPure)
	AActor* GetItemFromItemLocator(bool& _Success);

	//Returns the current InteractableItem
	UFUNCTION(BlueprintPure)
	UObject* GetInteractableItem();

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class UInteractableItemLocator> ItemLocator;

	//Calls interact on the new AActor parameter
	void Interact(AActor* _InteractableItem);

	//Calls stop interact on the current InteractableItem
	void StopInteract();

	//Sets up the timer to trigger StopInteract after a certain amount of time
	void HandleAutomaticInteraction();

#pragma endregion

#pragma region Variables

private:

	//The timer that triggers StopInteract (if required)
	FTimerHandle Timer;

	//Stores the InteractableItem to allow for StopInteract call
	TScriptInterface<IInteraction> InteractableItem;

#pragma endregion

#pragma region Delegates

public:

	FOnActionPerformed OnActionTriggered;
	FOnActionPerformed OnStopActionTriggered;

#pragma endregion
	
};
