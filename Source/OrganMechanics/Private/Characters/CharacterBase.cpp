// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CharacterBase.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/CharacterAttributeSet.h"

ACharacterBase::ACharacterBase() 
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(FName("AbilitySystemComponent"));
	AbilitySystemComponent->AddSpawnedAttribute(CharacterAttributeSet);
}

void ACharacterBase::UpdateCharacterSpeed(float _NewSpeed)
{
	CharacterAttributeSet->SetMaxWalkSpeed(_NewSpeed);
}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	UCharacterMovementComponent* _CMC = GetCharacterMovement();
	UpdateCharacterSpeed(GetCharacterMovement()->MaxWalkSpeed);
}

UCharacterAttributeSet* ACharacterBase::GetCharacterAttributeSet()
{
	return CharacterAttributeSet;
}
