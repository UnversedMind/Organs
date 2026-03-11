// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/DialogueSubsystem.h"

void UDialogueSubsystem::AcceptDialogue(UDataTable* _DataTable)
{
	CurrentDialogue = 0;
	StackedDialogue.Empty();
	_DataTable->GetAllRows<FDialogueStruct>(FString(""), StackedDialogue);
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
