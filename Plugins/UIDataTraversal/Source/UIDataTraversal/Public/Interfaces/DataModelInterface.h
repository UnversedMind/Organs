// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DataModelInterface.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDataChanged);
DECLARE_DYNAMIC_DELEGATE(FDataChanged);

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDataModelInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UIDATATRAVERSAL_API IDataModelInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	class UPropertyBridge* GetData();
	virtual class UPropertyBridge* GetData_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	class UControlBridge* GetControls();
	virtual class UControlBridge* GetControls_Implementation();

};
