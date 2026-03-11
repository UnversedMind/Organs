// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CommonEnums.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum ENotificationType : uint8
{
	None,
	System,
	Item,
	Value,
	MAX
};
