// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/Interaction.h"
#include "Food.generated.h"

UCLASS()
class ORGANMECHANICS_API AFood : public AActor, public IInteraction, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	AFood();
	
	//Calls the attribute set 'OrganUse' function, and triggers 'StopInteraction' timer
	void Interact_Implementation(bool& _Success) override;

private:

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float HealthRegainedDefaultValue = 5.0f;

	//returns the ability system component
	class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	//The ability system component on this actor
	UPROPERTY()
	class UAbilitySystemComponent* AbilitySystemComponent;

public:
	//Food attribute set - contains a number of variables relevant to the specific food
	UPROPERTY(EditDefaultsOnly, Instanced)
	class UFoodAttributeSet* FoodAttributeSet;

};
