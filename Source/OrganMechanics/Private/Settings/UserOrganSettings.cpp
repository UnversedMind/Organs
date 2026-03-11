// Fill out your copyright notice in the Description page of Project Settings.


#include "Settings/UserOrganSettings.h"
#include "Manager/ProgressManagerSubsystem.h"

UUserOrganSettings* UUserOrganSettings::GetUserOrganSettings()
{
    return Cast<UUserOrganSettings>(UGameUserSettings::GetGameUserSettings());
}

FName UUserOrganSettings::GetHotKeyOrgan(EOrganType _OrganType)
{
    return *OrganHotKeys.Find(_OrganType);
}

void UUserOrganSettings::SetOrganHotKey(EOrganType _OrganType, FName _OrganName, UObject* WorldContextObject)
{
    UProgressManagerSubsystem* progressManager = UProgressManagerSubsystem::GetProgressManager(WorldContextObject);
    if (!progressManager->GetIsOrganUnlocked(_OrganName)) 
    {
        return;
    }
    OrganHotKeys.Add(_OrganType, _OrganName);
    OnHotKeyOrganChanged.Broadcast(_OrganName, _OrganType);
}
