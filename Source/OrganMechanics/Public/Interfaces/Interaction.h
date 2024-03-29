// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interaction.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UInteraction : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ORGANMECHANICS_API IInteraction
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void CanUserInteract(bool& _Success);
	virtual void CanUserInteract_Implementation(bool& _Success);

	//Start interaction if not single shot, trigger interaction if single shot
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Interact(bool& _Success);
	virtual void Interact_Implementation(bool& _Success);

	//Ends interaction if not single shot
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StopInteract(bool& _Success);
	virtual void StopInteract_Implementation(bool& _Success);

	//Returns if the interaction should be a single interaction, or if the interaction should require 
	//'StopInteract' to be called before the interaction is considered complete
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool IsSingleShotInteraction();
	virtual bool IsSingleShotInteraction_Implementation();

	//In the case of an interaction ending automatically after a certain amount of time, returns that
	//amount of time
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	float GetInteractionTime();
	virtual float GetInteractionTime_Implementation();
};
