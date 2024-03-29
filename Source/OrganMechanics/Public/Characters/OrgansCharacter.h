// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharacterBase.h"
#include "AbilitySystemInterface.h"
#include "OrgansCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeOrganName, FName, OrganName);


UCLASS(Blueprintable)
class ORGANMECHANICS_API AOrgansCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:

#pragma region Functions

	//The list of organs the player will be able to use
	UPROPERTY(EditDefaultsOnly, Category = "OrganClasses")
	TArray<TSubclassOf<class AOrganBase>> OrganClasses;

	//Returns the full list of organs
	UFUNCTION(BlueprintPure)
	TArray<AOrganBase*> GetOrgans();

	//Overridden to allow spawning of organs
	virtual void BeginPlay() override;

	//Overriden to allow attribute set to Tick
	virtual void Tick(float DeltaSeconds) override;

	//Returns the organ the character is currently using
	UFUNCTION(BlueprintPure)
	class AOrganBase* GetActiveOrgan();

	//Returns the name of the active organ
	UFUNCTION(BlueprintPure)
	FName GetActiveOrganName();

	//Sets the active organ
	UFUNCTION(BlueprintCallable)
	void SetActiveOrgan(FName _NewActiveOrgan);

#pragma endregion

#pragma region Delegates

public:

	//Called when the active organ is changed
	UPROPERTY(BlueprintAssignable)
	FOnChangeOrganName OnOrganNameChanged;

#pragma endregion

#pragma region Variables

private:

	//The organs on the character
	TArray<AOrganBase*> Organs;

	//The current active organ
	FName CurrentActiveOrgan;

#pragma endregion

};
