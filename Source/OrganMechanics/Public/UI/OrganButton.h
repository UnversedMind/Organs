// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Settings/OrganSettings.h"
#include "OrganButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOrganSelected, FName, _OrganName);

/**
 * A button that shows an organ, based on the supplied organ name
 */
UCLASS()
class ORGANMECHANICS_API UOrganButton : public UButton
{
	GENERATED_BODY()

public:

#pragma region Variables

	//Supplied Organ Name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetOrganName", meta = (GetOptions = "GetOrganNames"), Category = "Config")
	FName OrganName;

	//Normal Button Tint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FLinearColor NormalTint = FLinearColor(0.5, 0.5, 0.5, 1.0);

	//Hover Button Tint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FLinearColor HoverTint = FLinearColor(0.724268, 0.724268, 0.724268, 1.0);

	//Press Button Tint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FLinearColor PressTint = FLinearColor(0.25, 0.25, 0.25, 1.0);

	//Disabld Button Tint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FLinearColor DisabledTint = FLinearColor(0.0, 0.0, 0.0, 1.0);

	//Used to increase or decrease the desired size of the button
	UPROPERTY(EditAnywhere, Category = "Config")
	float SizeMultiplier = 1.0f;

#pragma endregion

#pragma region Functions

#pragma region OrganNameFunctions
	//Sets the Organ Name
	UFUNCTION(BlueprintCallable)
	void SetOrganName(FName _NewOrganName);

	//Returns the Organ Name
	const FName& GetOrganName() const;

	//Allows OrganName to only be set to one of the specific organ names
	UFUNCTION()
	TArray<FName> GetOrganNames();

#pragma endregion

#pragma region UpdateAppearanceFunctions

	//Updates brush appearance
	UFUNCTION()
	void UpdateBrush();

	//Updates the image used on the button
	void UpdateResourceObjectOnButton(UTexture2D* _Resource);

private:

	//Updates the slate brush with the appropriate tint and texture
	FSlateBrush UpdateSlateBrush(FSlateBrush _SlateBrush, FLinearColor _BrushTint, UTexture2D* _Resource);

	//Allows widget appearance to be updated when OrganName changed in editor
	void SynchronizeProperties() override;

#pragma endregion

#pragma region Bindings

	virtual TSharedRef<SWidget> RebuildWidget() override;

	//Allows binding of organbuttonclicked
	UFUNCTION()
	void OrganButtonClicked();

	//Allows binding of organbuttonpressed
	UFUNCTION()
	void OrganButtonPressed();

	//Allows binding of organbuttonreleased
	UFUNCTION()
	void OrganButtonReleased();

#pragma endregion

#pragma endregion
	
public:

	UPROPERTY(BlueprintAssignable)
	FOnOrganSelected OnOrganButtonClicked;

	UPROPERTY(BlueprintAssignable)
	FOnOrganSelected OnOrganButtonPressed;

	UPROPERTY(BlueprintAssignable)
	FOnOrganSelected OnOrganButtonReleased;
};
