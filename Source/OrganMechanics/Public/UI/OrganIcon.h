// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Image.h"
#include "Settings/OrganSettings.h"
#include "OrganIcon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIconChanged, FName, NewOrganName);

/**
 * An image that shows an organ, based on the supplied organ name
 */
UCLASS()
class ORGANMECHANICS_API UOrganIcon : public UImage
{
	GENERATED_BODY()

public:

#pragma region Variables

	//Supplied organ name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, BlueprintSetter = "SetOrganName", meta = (GetOptions = "GetOrganNames"), Category = "Config")
	FName OrganName;

	//Used to increase or decrease the desired size of the image
	UPROPERTY(EditAnywhere, Category = "Config")
	float SizeMultiplier = 1.0f;

#pragma endregion

#pragma region Functions

	//Updates widget appearance
	UFUNCTION(BlueprintCallable)
	void OnSetOrganName();

	//Allows OrganName to be set in blueprint
	UFUNCTION(BlueprintCallable)
	void SetOrganName(FName _NewOrganName);

	//Returns OrganName
	UFUNCTION(BlueprintCallable)
	const FName& GetOrganName() const;

	//Allows OrganName to only be set to one of the specific organ names
	UFUNCTION()
	TArray<FName> GetOrganNames();

protected:

	//Allows changing of OrganName to automatically update widget in editor view
	void SynchronizeProperties() override;

#pragma endregion

#pragma region Delegates

public:

	UPROPERTY(BlueprintAssignable)
	FOnIconChanged OnIconChanged;
	
};
