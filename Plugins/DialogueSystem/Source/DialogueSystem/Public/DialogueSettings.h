// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "DialogueSettings.generated.h"

/**
 * 
 */
UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "Dialogue Settings"))
class DIALOGUESYSTEM_API UDialogueSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure)
	static TArray<FName> GetCharacterNames();

	UFUNCTION(BlueprintPure)
	static TArray<FName> GetCharacterVariables();

private:

	UPROPERTY(EditAnywhere, Config, meta = (AllowPrivateAccess = "true"))
	TArray<FName> CharacterNames;

	UPROPERTY(EditAnywhere, Config, meta = (AllowPrivateAccess = "true"))
	TArray<FName> CharacterVariables;
	
};
