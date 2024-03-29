// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/OrganIcon.h"

void UOrganIcon::OnSetOrganName()
{
	TArray<FName> rowNames = GetOrganNames();
	if (rowNames.Contains(GetOrganName()))
	{
		SetColorAndOpacity(UOrganSettings::GetImageTint(GetOrganName()));
		TObjectPtr<UTexture2D> organTexture = UOrganSettings::GetImageTexture(GetOrganName());
		SetBrushFromTexture(organTexture, true);
		FVector2D desiredSize = FVector2D((organTexture->GetImportedSize().X * SizeMultiplier), (organTexture->GetImportedSize().Y * SizeMultiplier));
		SetDesiredSizeOverride(desiredSize);
	}
}

void UOrganIcon::SetOrganName(FName _NewOrganName)
{
	OrganName = _NewOrganName;
	OnIconChanged.Broadcast(OrganName);
	OnSetOrganName();
}

const FName& UOrganIcon::GetOrganName() const
{
	return OrganName;
}

TArray<FName> UOrganIcon::GetOrganNames()
{
	return UOrganSettings::GetOrganNames();
}

void UOrganIcon::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	SetOrganName(OrganName);
}
