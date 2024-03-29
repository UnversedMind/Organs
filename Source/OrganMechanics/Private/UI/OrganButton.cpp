// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/OrganButton.h"

void UOrganButton::SetOrganName(FName _NewOrganName)
{
	OrganName = _NewOrganName;
	UpdateBrush();
}

const FName& UOrganButton::GetOrganName() const
{
	return OrganName;
}

TArray<FName> UOrganButton::GetOrganNames()
{
	return UOrganSettings::GetOrganNames();
}

void UOrganButton::UpdateBrush()
{
	TArray<FName> rowNames = GetOrganNames();
	if (rowNames.Contains(OrganName))
	{
		UpdateResourceObjectOnButton(UOrganSettings::GetImageTexture(OrganName));
		SetBackgroundColor(UOrganSettings::GetImageTint(OrganName));
	}
}

void UOrganButton::UpdateResourceObjectOnButton(UTexture2D* _Resource)
{
	FButtonStyle tempStyle = GetStyle();
	tempStyle.SetNormal(UpdateSlateBrush(GetStyle().Normal, NormalTint, _Resource));
	tempStyle.SetHovered(UpdateSlateBrush(GetStyle().Hovered, HoverTint, _Resource));
	tempStyle.SetPressed(UpdateSlateBrush(GetStyle().Pressed, PressTint, _Resource));
	tempStyle.SetDisabled(UpdateSlateBrush(GetStyle().Disabled, DisabledTint, _Resource));
	SetStyle(tempStyle);
}

FSlateBrush UOrganButton::UpdateSlateBrush(FSlateBrush _SlateBrush, FLinearColor _BrushTint, UTexture2D* _Resource)
{
	_SlateBrush.DrawAs = ESlateBrushDrawType::Type::Image;
	FVector2D imageSize = FVector2D(_Resource->GetSizeX(), _Resource->GetSizeY());
	_SlateBrush.SetResourceObject(_Resource);
	_SlateBrush.SetImageSize(imageSize * SizeMultiplier);
	_SlateBrush.TintColor = _BrushTint;
	return _SlateBrush;
}

void UOrganButton::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	SetOrganName(OrganName);
}

TSharedRef<SWidget> UOrganButton::RebuildWidget()
{
	OnClicked.RemoveAll(this);
	OnClicked.AddDynamic(this, &UOrganButton::OrganButtonClicked);
	OnPressed.RemoveAll(this);
	OnPressed.AddDynamic(this, &UOrganButton::OrganButtonPressed);
	OnReleased.RemoveAll(this);
	OnReleased.AddDynamic(this, &UOrganButton::OrganButtonReleased);
	return Super::RebuildWidget();
}

void UOrganButton::OrganButtonClicked()
{
	OnOrganButtonClicked.Broadcast(OrganName);
}

void UOrganButton::OrganButtonPressed()
{
	OnOrganButtonPressed.Broadcast(OrganName);
}

void UOrganButton::OrganButtonReleased()
{
	OnOrganButtonReleased.Broadcast(OrganName);
}
