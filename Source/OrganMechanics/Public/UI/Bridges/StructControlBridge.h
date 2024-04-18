// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Bridges/ControlBridge.h"
#include "StructControlBridge.generated.h"

DECLARE_DELEGATE_TwoParams(FOnStructChanged, FStructProperty*, uint8*);

/**
 * 
 */
UCLASS()
class ORGANMECHANICS_API UStructControlBridge : public UControlBridge
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, CustomThunk, meta = (CustomStructureParam = "_NewValue"))
	void UpdateValue(UStruct* _NewValue);

	template <typename UserClass, typename StructClass>
	void BindObject(UserClass* InObject, typename TMemFunPtrType<false, UserClass, void(StructClass)>::Type InFunc)
	{
		TDelegate<void(StructClass)> NewDelegate;
		NewDelegate.BindUObject(InObject, InFunc);

		OnStructChanged.BindLambda([NewDelegate, this](FStructProperty* _Struct, uint8* _Container) 
		{
			StructClass* _StructData = _Struct->ContainerPtrToValuePtr<StructClass>(_Container);

			NewDelegate.Execute(*_StructData);
		});
	}

	DECLARE_FUNCTION(execUpdateValue)
	{
		// Steps into the stack, walking to the next property in it
		Stack.Step(Stack.Object, NULL);

		// Grab the last property found when we walked the stack
		// This does not contains the property value, only its type information
		FStructProperty* StructProperty = CastField<FStructProperty>(Stack.MostRecentProperty);

		// Grab the base address where the struct actually stores its data
		// This is where the property value is truly stored
		UStructControlBridge* StructControlBridge = Cast<UStructControlBridge>(Context);

		uint8* StructPropertyContainer = Stack.MostRecentPropertyContainer;

		// We need this to wrap up the stack
		P_FINISH;

		StructControlBridge->OnStructChanged.Execute(StructProperty, StructPropertyContainer);
	}

private:

	FOnStructChanged OnStructChanged;
	
};
