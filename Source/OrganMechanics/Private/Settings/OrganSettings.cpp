// Fill out your copyright notice in the Description page of Project Settings.


#include "Settings/OrganSettings.h"

UOrganSettings::UOrganSettings()
{
	OrganTableInstance = OrganTable.LoadSynchronous();
}

UDataTable* UOrganSettings::GetDataTable()
{
	const UOrganSettings* OSettings = GetDefault<UOrganSettings>();

	if (!OSettings->OrganTableInstance) 
	{
		return OSettings->OrganTable.LoadSynchronous();
	}

	return OSettings->OrganTableInstance;
}

TArray<FName> UOrganSettings::GetOrganNames()
{
	return GetDataTable()->GetRowNames();
}

TSubclassOf<UGameplayEffect> UOrganSettings::GetGameplayEffect(FGameplayAttribute _GameplayAttribute)
{
	const UOrganSettings* OSettings = GetDefault<UOrganSettings>();
	FString attributeName = _GameplayAttribute.GetName();
	return OSettings->GameplayEffect[attributeName];
}

UTexture2D* UOrganSettings::GetImageTexture(FName _OrganName)
{
	TObjectPtr<UDataTable> OrganTable = GetDataTable();
	return OrganTable.Get()->FindRow<FOrganUIInfo>(_OrganName, "")->OrganTexture;
}

FLinearColor UOrganSettings::GetImageTint(FName _OrganName)
{
	TObjectPtr<UDataTable> OrganTable = GetDataTable();
	return OrganTable.Get()->FindRow<FOrganUIInfo>(_OrganName, "")->OrganTint;
}

UStaticMesh* UOrganSettings::GetWeaponMesh(FName _OrganName)
{
	TObjectPtr<UDataTable> OrganTable = GetDataTable();
	EWeaponType weaponType = OrganTable.Get()->FindRow<FOrganUIInfo>(_OrganName, "")->OrganWeaponType;
	return GetWeaponMeshes().Find(weaponType)->LoadSynchronous();
}

TMap<EWeaponType, TSoftObjectPtr<UStaticMesh>> UOrganSettings::GetWeaponMeshes()
{
	const UOrganSettings* OSettings = GetDefault<UOrganSettings>();
	return OSettings->WeaponMeshes;
}
