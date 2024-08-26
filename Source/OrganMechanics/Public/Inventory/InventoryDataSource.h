// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/DataModelInterface.h"
#include "InventoryDataSource.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ORGANMECHANICS_API UInventoryDataSource : public UActorComponent, public IDataModelInterface
{
	GENERATED_BODY()

public:

	virtual class UPropertyBridge* GetData_Implementation() override;

};
