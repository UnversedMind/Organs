// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/ProgressManagerSubsystem.h"
#include "Kismet/GameplayStatics.h"

UProgressManagerSubsystem* UProgressManagerSubsystem::GetProgressManager(UObject* WorldContextObject)
{
    UProgressManagerSubsystem* progressManager = UGameplayStatics::GetGameInstance(WorldContextObject)->GetSubsystem<UProgressManagerSubsystem>();
    return progressManager;
}

bool UProgressManagerSubsystem::GetIsOrganUnlocked(FName _OrganName)
{
    return *IsOrganUnlocked.Find(_OrganName);
}

TArray<FName> UProgressManagerSubsystem::GetUnlockedOrgans()
{
    TArray<FName> unlockedOrgans;
    for (TPair<FName, bool> organUnlockValue : IsOrganUnlocked)
    {
        if (organUnlockValue.Value)
        {
            unlockedOrgans.Add(organUnlockValue.Key);
        }
    }
    return unlockedOrgans;
}

bool UProgressManagerSubsystem::HasOrganInMap(FName _OrganName)
{
    return IsOrganUnlocked.Contains(_OrganName);
}

void UProgressManagerSubsystem::AddOrgan(FName _OrganName, bool _IsUnlocked)
{
    IsOrganUnlocked.Add(_OrganName, _IsUnlocked);
}

void UProgressManagerSubsystem::UnlockOrgan(FName _OrganName)
{
    AddOrgan(_OrganName, true);
}

TMap<FName, bool> UProgressManagerSubsystem::GetOrganUnlockMap()
{
    return IsOrganUnlocked;
}
