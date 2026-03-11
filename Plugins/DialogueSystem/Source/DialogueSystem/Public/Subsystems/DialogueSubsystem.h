// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Structs/DialogueStruct.h"
#include "DialogueSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnProgressionCompleted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueProgressed);

/**
 * 
 */
UCLASS()
class DIALOGUESYSTEM_API UDialogueSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void AcceptDialogue(UDataTable* _DataTable);

	void InsertDialogue(UDataTable* _DataTable);

	UFUNCTION(BlueprintCallable)
	void ProgressDialogue();

	UFUNCTION(BlueprintPure)
	bool DoesCurrentDialogueHaveChoices();

	UFUNCTION(BlueprintCallable)
	void OnChoiceSelected(FDialogueOptionEffect _ChoiceSelected);

	UFUNCTION(BlueprintPure)
	FDialogueStruct GetCurrentDialogue();

	UPROPERTY(BlueprintAssignable)
	FOnProgressionCompleted OnProgressionCompleted;

	UPROPERTY(BlueprintAssignable)
	FOnDialogueProgressed OnDialogueProgressed;

private:

	TArray<FDialogueStruct*> StackedDialogue;

	FDialogueStruct GetDialogueAtIndex(int _Index);

	int CurrentDialogue;
	
};
