// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "AttributeSet.h"
#include "OrganSettings.generated.h"

//Types of weapon
UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Sharp			UMETA(DisplayName = "Sharp"),
	Hammer			UMETA(DisplayName = "Hammer"),
	Blunt			UMETA(DisplayName = "Blunt")
};

//Config visual info - in data table, will be one row per organ
USTRUCT(Blueprintable, BlueprintType)
struct FOrganUIInfo : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* OrganTexture;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FLinearColor OrganTint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EWeaponType OrganWeaponType;
};

/**
 * Settings to allow organ visual config (for example, UI tint), weapon config, and GameplayEffect config
 */
UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "Organ Settings"))
class ORGANMECHANICS_API UOrganSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	UOrganSettings();

	//OrganTable with rows of FOrganUIInfo - allows config for organ visuals
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General", AdvancedDisplay)
	TSoftObjectPtr<UDataTable> OrganTable;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly)
	TMap<FString, TSubclassOf<class UGameplayEffect>> GameplayEffect;

	//Returns the OrganTable
	static UDataTable* GetDataTable();

	//Returns an array of OrganNames
	UFUNCTION(BlueprintPure)
	static TArray<FName> GetOrganNames();

	UFUNCTION(BlueprintPure)
	static TSubclassOf<class UGameplayEffect> GetGameplayEffect(FGameplayAttribute _GameplayAttribute);

	UFUNCTION(BlueprintPure)
	//Gets an organ's image texture from the OrganTable config
	static UTexture2D* GetImageTexture(FName _OrganName);

	//Gets an organ's image tint from the OrganTable config
	UFUNCTION(BlueprintPure)
	static FLinearColor GetImageTint(FName _OrganName);

	//Gets the relevant weapon mesh from the WeaponMeshes map
	UFUNCTION(BlueprintPure)
	static UStaticMesh* GetWeaponMesh(FName _OrganName);

	//Returns the WeaponMeshes map
	static TMap<EWeaponType, TSoftObjectPtr<UStaticMesh>> GetWeaponMeshes();

	//Map of weapon type to static mesh
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General")
	TMap<EWeaponType, TSoftObjectPtr<UStaticMesh>> WeaponMeshes;

private:

	UDataTable* OrganTableInstance;
	
};
