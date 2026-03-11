// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueSettings.h"

TArray<FName> UDialogueSettings::GetCharacterNames()
{
	const UDialogueSettings* dialogueSettings = GetDefault<UDialogueSettings>();
	return dialogueSettings->CharacterNames;
}

TArray<FName> UDialogueSettings::GetCharacterVariables()
{
	const UDialogueSettings* dialogueSettings = GetDefault<UDialogueSettings>();
	return dialogueSettings->CharacterVariables;
}