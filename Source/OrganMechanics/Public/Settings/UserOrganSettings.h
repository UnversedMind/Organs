// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "Organs/OrganBase.h"
#include "UserOrganSettings.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHotKeyOrganChanged, FName, OrganName, EOrganType, OrganType);

/**
 * Stores user settings about which organs are currently unlocked
 */
UCLASS()
class ORGANMECHANICS_API UUserOrganSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:

	//Returns the user settings of this type
	UFUNCTION(BlueprintCallable)
	static UUserOrganSettings* GetUserOrganSettings();

	//Keeps track of which organs are unlocked
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FName, bool> IsOrganUnlocked;

	//Returns if the specified organ is unlocked
	UFUNCTION(BlueprintPure)
	bool GetIsOrganUnlocked(FName _OrganName);

	//Adds the organ to IsOrganUnlocked map
	UFUNCTION(BlueprintCallable)
	void AddOrgan(FName _OrganName, bool _IsUnlocked);

	//Unlocks the organ
	UFUNCTION(BlueprintCallable)
	void UnlockOrgan(FName _OrganName);

	//Returns the name of the organ at the specified hotkey type
	UFUNCTION(BlueprintPure)
	FName GetHotKeyOrgan(EOrganType _OrganType);

	//Sets the organ to be linked to the relevant hotkey
	UFUNCTION(BlueprintCallable)
	void SetOrganHotKey(EOrganType _OrganType, FName _OrganName);

	//Called when the organ assigned to a hotkey is changed
	UPROPERTY(BlueprintAssignable)
	FOnHotKeyOrganChanged OnHotKeyOrganChanged;

	//A map of the organ system (i.e. Filtration) to the hotkey organ
	TMap<EOrganType, FName> OrganHotKeys;
	
};
