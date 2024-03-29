// Fill out your copyright notice in the Description page of Project Settings.


#include "Settings/UserOrganSettings.h"

UUserOrganSettings* UUserOrganSettings::GetUserOrganSettings()
{
    return Cast<UUserOrganSettings>(UGameUserSettings::GetGameUserSettings());
}

bool UUserOrganSettings::GetIsOrganUnlocked(FName _OrganName)
{
    return *IsOrganUnlocked.Find(_OrganName);
}

void UUserOrganSettings::AddOrgan(FName _OrganName, bool _IsUnlocked)
{
    IsOrganUnlocked.Add(_OrganName, _IsUnlocked);
}

void UUserOrganSettings::UnlockOrgan(FName _OrganName)
{
    AddOrgan(_OrganName, true);
}

FName UUserOrganSettings::GetHotKeyOrgan(EOrganType _OrganType)
{
    return *OrganHotKeys.Find(_OrganType);
}

void UUserOrganSettings::SetOrganHotKey(EOrganType _OrganType, FName _OrganName)
{
    if (!GetIsOrganUnlocked(_OrganName)) 
    {
        return;
    }
    OrganHotKeys.Add(_OrganType, _OrganName);
    OnHotKeyOrganChanged.Broadcast(_OrganName, _OrganType);
}
