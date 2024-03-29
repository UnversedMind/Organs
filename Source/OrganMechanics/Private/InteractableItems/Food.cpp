// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableItems/Food.h"
#include "AbilitySystemComponent.h"
#include "InteractableItems/FoodAttributeSet.h"

AFood::AFood() 
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(FName("AbilitySystemComponent"));
	AbilitySystemComponent->AddSpawnedAttribute(FoodAttributeSet);
}

void AFood::Interact_Implementation(bool& _Success) 
{
	Destroy();
	_Success = true;
}

UAbilitySystemComponent* AFood::GetAbilitySystemComponent() const 
{
	return AbilitySystemComponent;
}

