// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueStruct.generated.h"

UENUM(BlueprintType)
enum EModifierType : uint8
{
	Increase		UMETA(DisplayName="Increase"),
	Decrease		UMETA(DisplayName="Decrease"),
	Set				UMETA(DisplayName="Set"),
	Insert			UMETA(DisplayName="Insert")
};

USTRUCT(BlueprintType)
struct DIALOGUESYSTEM_API FDialogueOptionEffect : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<EModifierType> FunctionType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "FunctionType!=EModifierType::Insert"))
	FName CharacterName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "FunctionType!=EModifierType::Insert"))
	FName AttributeToAffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "FunctionType!=EModifierType::Insert"))
	float Value;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "FunctionType==EModifierType::Insert"))
	TObjectPtr<UDataTable> DataTableToImport;
};

USTRUCT(BlueprintType)
struct DIALOGUESYSTEM_API FDialogueStruct : public FTableRowBase
{
	GENERATED_BODY()

public:

	FDialogueStruct() 
	{

	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName SpeakingCharacter;

	UPROPERTY(EditDefaultsOnly)
	FName Emotion;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString CharacterText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FDialogueOptionEffect> Options;
		
};
