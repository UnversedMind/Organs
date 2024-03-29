// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "InteractionEventSubsystem.generated.h"

DECLARE_DYNAMIC_DELEGATE(FInteractionEvent);
DECLARE_DYNAMIC_DELEGATE_OneParam(FItemInteractionEvent, UObject*, _InteractableItem);

/**
 * 
 */
UCLASS(Blueprintable)
class ORGANMECHANICS_API UInteractionEventSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void BindEventToClassInteraction(class UInteractionController* _InteractionController, TSubclassOf<UObject> _InteractableClass, FInteractionEvent _SuccessInteractionEvent, FInteractionEvent _FailureInteractionEvent);
	
	UFUNCTION(BlueprintCallable)
	void BindEventToObjectInteraction(class UInteractionController* _InteractionController, UObject* _Interactable, FInteractionEvent _SuccessInteractionEvent, FInteractionEvent _FailureInteractionEvent);

	UFUNCTION(BlueprintCallable)
	void BindEventToClassStopInteraction(class UInteractionController* _InteractionController, TSubclassOf<UObject> _InteractableClass, FInteractionEvent _SuccessStopInteractionEvent, FInteractionEvent _FailureStopInteractionEvent);

	UFUNCTION(BlueprintCallable)
	void BindEventToObjectStopInteraction(class UInteractionController* _InteractionController, UObject* _Interactable, FInteractionEvent _SuccessStopInteractionEvent, FInteractionEvent _FailureStopInteractionEvent);

	UFUNCTION(BlueprintCallable)
	void BindEventToClassInteractionWithReturn(class UInteractionController* _InteractionController, TSubclassOf<UObject> _InteractableClass, FItemInteractionEvent _SuccessInteractionEvent, FItemInteractionEvent _FailureInteractionEvent);

	UFUNCTION(BlueprintCallable)
	void BindEventToObjectInteractionWithReturn(class UInteractionController* _InteractionController, UObject* _Interactable, FItemInteractionEvent _SuccessInteractionEvent, FItemInteractionEvent _FailureInteractionEvent);

	UFUNCTION(BlueprintCallable)
	void BindEventToClassStopInteractionWithReturn(class UInteractionController* _InteractionController, TSubclassOf<UObject> _InteractableClass, FItemInteractionEvent _SuccessStopInteractionEvent, FItemInteractionEvent _FailureStopInteractionEvent);

	UFUNCTION(BlueprintCallable)
	void BindEventToObjectStopInteractionWithReturn(class UInteractionController* _InteractionController, UObject* _Interactable, FItemInteractionEvent _SuccessStopInteractionEvent, FItemInteractionEvent _FailureStopInteractionEvent);
};
