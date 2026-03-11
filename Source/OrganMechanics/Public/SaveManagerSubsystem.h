// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SaveManagerSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class ORGANMECHANICS_API USaveManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure)
	FName GetSaveSlotName();

	UFUNCTION(BlueprintCallable)
	void SetSaveSlotName(FName _SlotName);

private:

	FName SlotName;
	
};
