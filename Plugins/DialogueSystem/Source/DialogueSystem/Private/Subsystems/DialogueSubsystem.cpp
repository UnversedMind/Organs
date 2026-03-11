// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/DialogueSubsystem.h"

void UDialogueSubsystem::AcceptDialogue(UDataTable* _DataTable)
{
	CurrentDialogue = 0;
	StackedDialogue.Empty();
	_DataTable->GetAllRows<FDialogueStruct>(FString(""), StackedDialogue);
}

void UDialogueSubsystem::InsertDialogue(UDataTable* _DataTable)
{
	TArray<FDialogueStruct*> dialogueToInsert;
	_DataTable->GetAllRows<FDialogueStruct>(FString(""), dialogueToInsert);
	StackedDialogue.Insert(dialogueToInsert, (CurrentDialogue+1));
}

void UDialogueSubsystem::ProgressDialogue()
{
	CurrentDialogue++;
	if (!StackedDialogue.IsValidIndex(CurrentDialogue)) 
	{
		OnProgressionCompleted.Broadcast();
		return;
	}
	OnDialogueProgressed.Broadcast();
}

bool UDialogueSubsystem::DoesCurrentDialogueHaveChoices()
{
	FDialogueStruct dialogueStruct = GetCurrentDialogue();
	if (dialogueStruct.Options.IsEmpty()) {
		return false;
	}
	return true;
}

void UDialogueSubsystem::OnChoiceSelected(FDialogueOptionEffect _ChoiceSelected)
{
	if (_ChoiceSelected.FunctionType == EModifierType::Insert) {
		InsertDialogue(_ChoiceSelected.DataTableToImport);
	}
	ProgressDialogue();
}

FDialogueStruct UDialogueSubsystem::GetCurrentDialogue()
{
	return GetDialogueAtIndex(CurrentDialogue);
}

FDialogueStruct UDialogueSubsystem::GetDialogueAtIndex(int _Index)
{
	if (!StackedDialogue.IsValidIndex(_Index)) 
	{
		return FDialogueStruct();
	}
	return *StackedDialogue[_Index];
}
