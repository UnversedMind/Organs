// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/OrgansCharacter.h"
#include "Organs/OrganBase.h"
#include "AbilitySystemComponent.h"
#include "Characters/CharacterAttributeSet.h"
#include "Settings/UserOrganSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Organs/OrganBaseAttributeSet.h"
#include "Manager/ProgressManagerSubsystem.h"

TArray<class AOrganBase*> AOrgansCharacter::GetOrgans()
{
    return Organs;
}

void AOrgansCharacter::BeginPlay()
{
    Super::BeginPlay();
    UUserOrganSettings* _Settings = UUserOrganSettings::GetUserOrganSettings();
    for (TSubclassOf<AOrganBase> organ : OrganClasses)
    {
        TObjectPtr<AOrganBase> newOrgan = GetWorld()->SpawnActor<AOrganBase>(organ, GetActorTransform());
        newOrgan.Get()->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
        Organs.Add(newOrgan);
        newOrgan->OnAttachToActor();

        UProgressManagerSubsystem* progressManager = UProgressManagerSubsystem::GetProgressManager(this);
        if (!progressManager->HasOrganInMap(newOrgan->GetOrganName())) 
        {
            progressManager->AddOrgan(newOrgan->GetOrganName(), newOrgan->GetStartUnlocked());
            _Settings->SetOrganHotKey(newOrgan->GetOrganType(), newOrgan->GetOrganName(), this);
        }
    }

    if (GetActiveOrganName() == FName()) 
    {
        SetActiveOrgan(_Settings->GetHotKeyOrgan(EOrganType::Respiratory));
        return;
    }
    SetActiveOrgan(GetActiveOrganName());
}

void AOrgansCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    CharacterAttributeSet->OnTick();
}

AOrganBase* AOrgansCharacter::GetActiveOrgan()
{
    AOrganBase* activeOrgan = nullptr;
    for (TObjectPtr<AOrganBase> organ : Organs) 
    {
        if (organ.Get()->GetOrganName() == CurrentActiveOrgan) 
        {
            activeOrgan = organ;
            break;
        }
    }
    return activeOrgan;
}

FName AOrgansCharacter::GetActiveOrganName()
{
    return CurrentActiveOrgan;
}

void AOrgansCharacter::SetActiveOrgan(FName _NewActiveOrgan)
{
    CurrentActiveOrgan = _NewActiveOrgan;
    OnOrganNameChanged.Broadcast(_NewActiveOrgan);
}
