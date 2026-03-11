// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterInfo.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct DIALOGUESYSTEM_API FCharacterInfo : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName CharacterName;

};

