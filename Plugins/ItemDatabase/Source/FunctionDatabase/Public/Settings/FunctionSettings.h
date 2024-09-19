// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Functions/FunctionListInfo.h"
#include "FunctionSettings.generated.h"

/**
 * 
 */

UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "Function Settings"))
class FUNCTIONDATABASE_API UFunctionSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	UFUNCTION()
	static TArray<FName> GetFunctionIdentifiers();

	UFUNCTION()
	static FFunctionInfo GetFunctionInfoFromIdentifier(FName _FunctionIdentifier);

	UFUNCTION(BlueprintPure)
	static TArray<FFunctionInfo> GetFunctionInfoFromIdentifiers(TArray<FName> _FunctionIdentifiers);

private:

	//Loads the data table
	UFunctionSettings();

	//Function that loads the function data table
	void LoadFunctionDataTable();

	//Returns the item data table
	const UDataTable* GetFunctionDataTable();

	//The soft object ptr to the item data table
	UPROPERTY(EditAnywhere, Config, meta = (RequiredAssetDataTags = "RowStructure=/Script/FunctionDatabase.FunctionInfo", AllowPrivateAccess = "true"), Category = "Functions")
	TSoftObjectPtr<class UDataTable> FunctionList;

	//The object ptr to the item data table
	TObjectPtr<class UDataTable> FunctionListInstance;

};