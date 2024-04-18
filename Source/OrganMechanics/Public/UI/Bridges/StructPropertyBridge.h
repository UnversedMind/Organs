// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Bridges/PropertyBridge.h"
#include "StructPropertyBridge.generated.h"

/**
 * This class is used for any data that could be quantified in a struct - for example when data for a string and int needs to be passed 
 * at the same time
 */
UCLASS()
class ORGANMECHANICS_API UStructPropertyBridge : public UPropertyBridge
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	static UStructPropertyBridge* CreatePropertyBridge(TMap<FName, UPropertyBridge*> _Data);

	UPROPERTY(BlueprintReadOnly)
	TMap<FName, UPropertyBridge*> Data;

	UFUNCTION(BlueprintPure, meta = (DeterminesOutputType = "_Class"))
	UPropertyBridge* GetDataFromNameAs(FName _Name, TSubclassOf<UPropertyBridge> _Class);
	
};
