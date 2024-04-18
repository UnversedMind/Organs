// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Bridge.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ORGANMECHANICS_API UBridge : public UObject
{
	GENERATED_BODY()

protected:

	template <typename A>
	static A* CreateNewBridge(UObject* _Outer, TSubclassOf<A> _ChildType) 
	{
		A* _NewBridge = NewObject<A>(_Outer, _ChildType);
		return _NewBridge;
	}

	template <typename T>
	static T* CreateBridge()
	{
		T* _NewBridge = NewObject<T>();
		return _NewBridge;
	}
	
};
