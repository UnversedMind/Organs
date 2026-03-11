// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ProgressManagerSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class ORGANMECHANICS_API UProgressManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext))
	static UProgressManagerSubsystem* GetProgressManager(UObject* WorldContextObject);

	//Returns if the specified organ is unlocked
	UFUNCTION(BlueprintPure)
	bool GetIsOrganUnlocked(FName _OrganName);

	UFUNCTION(BlueprintPure)
	TArray<FName> GetUnlockedOrgans();

	UFUNCTION(BlueprintCallable)
	bool HasOrganInMap(FName _OrganName);

	//Adds the organ to IsOrganUnlocked map
	UFUNCTION(BlueprintCallable)
	void AddOrgan(FName _OrganName, bool _IsUnlocked);

	//Unlocks the organ
	UFUNCTION(BlueprintCallable)
	void UnlockOrgan(FName _OrganName);

	UFUNCTION(BlueprintPure)
	TMap<FName, bool> GetOrganUnlockMap();

private:

	TMap<FName, bool> IsOrganUnlocked;
	
};
