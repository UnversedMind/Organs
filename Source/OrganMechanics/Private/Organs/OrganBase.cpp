// Fill out your copyright notice in the Description page of Project Settings.


#include "Organs/OrganBase.h"
#include "Organs/OrganBaseAttributeSet.h"
#include "Characters/CharacterAttributeSet.h"
#include "AbilitySystemComponent.h"

AOrganBase::AOrganBase()
{
    AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(FName("AbilitySystemComponent"));
    AbilitySystemComponent->AddSpawnedAttribute(OrganAttributeSet);
    PrimaryActorTick.bCanEverTick = true;
}

UAbilitySystemComponent* AOrganBase::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

void AOrganBase::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    OrganAttributeSet->OnTick();
}

void AOrganBase::OnAttachToActor()
{
    OrganAttributeSet->PostAddAttributeSetToAbilitySystemComponent();
}

void AOrganBase::Interact_Implementation(bool& _Success)
{
    _Success = OnOrganUsed();
}

bool AOrganBase::IsSingleShotInteraction_Implementation()
{
    return false;
}

float AOrganBase::GetInteractionTime_Implementation()
{
    return 1.0f;
}

bool AOrganBase::OnOrganUsed()
{
    bool bSuccess = false;
    if (OrganAttributeSet->WouldOrganHealthBeLessThanZeroOnUse()) 
    {
        return bSuccess;
    }
    OrganAttributeSet->OnOrganUsed();
    bSuccess = true;
    return bSuccess;
}
