// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CharacterBase.generated.h"

UCLASS(Blueprintable)
class ORGANMECHANICS_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

#pragma region Functions

	ACharacterBase();

	UFUNCTION(BlueprintCallable)
	void UpdateCharacterSpeed(float _NewSpeed);

private:
	//returns the ability system component
	class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

#pragma endregion

#pragma region Variables

public:
	//Character attribute set - contains a number of variables relevant to the character
	UPROPERTY(EditDefaultsOnly, Instanced)
	class UCharacterAttributeSet* CharacterAttributeSet;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure)
	UCharacterAttributeSet* GetCharacterAttributeSet();

private:

	//The ability system component on this actor
	UPROPERTY()
	class UAbilitySystemComponent* AbilitySystemComponent;

#pragma endregion


};
