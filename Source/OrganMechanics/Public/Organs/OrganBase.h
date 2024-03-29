// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interaction.h"
#include "AbilitySystemInterface.h"
#include "OrganBase.generated.h"

//Organs are split up into different organ systems - this enum tells us which system an organ belongs to
UENUM(BlueprintType)
enum class EOrganType : uint8 
{
	Filtration		UMETA(DisplayName = "Filtration"),
	Digestive		UMETA(DisplayName = "Digestive"),
	Respiratory		UMETA(DisplayName = "Respiratory"),
	Sensory			UMETA(DisplayName = "Sensory")
};

UCLASS(Blueprintable)
class ORGANMECHANICS_API AOrganBase : public AActor, public IAbilitySystemInterface, public IInteraction
{
	GENERATED_BODY()

public:

	//Constructor to allow for attribute set functionality
	AOrganBase();

	//Organ attribute set - contains a number of variables relevant to the organ
	UPROPERTY(EditDefaultsOnly, Instanced)
	class UOrganBaseAttributeSet* OrganAttributeSet;

	//Returns the AbilitySystemComponent of this actor
	class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	//Returns this organ's name
	UFUNCTION(BlueprintPure)
	FName GetOrganName() 
	{
		return FName(OrganName);
	}

	//Returns if the organ should start unlocked
	UFUNCTION(BlueprintCallable)
	bool GetStartUnlocked() { return bStartUnlocked; };

	//Returns the system this organ belongs to
	UFUNCTION(BlueprintCallable)
	EOrganType GetOrganType() { return OrganType; };

	//Overriden to allow attribute set to Tick
	virtual void Tick(float DeltaSeconds) override;

	void OnAttachToActor();

	//Calls the attribute set 'OrganUse' function, and triggers 'StopInteraction' timer
	void Interact_Implementation(bool& _Success) override;

	//Overridden as is not a single shot interaction
	bool IsSingleShotInteraction_Implementation() override;

	//InteractionTime is now returned as a variable
	float GetInteractionTime_Implementation() override;

	//Time until the interaction should be marked as 'complete'
	float InteractionTime = 1.0f;

private:

	//Tells us if the organ should be unlocked by default
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bStartUnlocked;

	//The organ's name
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString OrganName;

	//The system this organ belongs to
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EOrganType OrganType;

	//The ability system component held on this actor
	UPROPERTY()
	class UAbilitySystemComponent* AbilitySystemComponent;

	//Allows the OrganAttributeSet to updated the attribute values
	bool OnOrganUsed();
		
};
