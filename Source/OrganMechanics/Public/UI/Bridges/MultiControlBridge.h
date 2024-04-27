// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Bridges/ControlBridge.h"
#include "MultiControlBridge.generated.h"

/**
 * 
 */
UCLASS()
class ORGANMECHANICS_API UMultiControlBridge : public UControlBridge
{
	GENERATED_BODY()

public:

	template<typename T>
	void log(T obj)
	{
		//std::cout << obj;
	}

	template<typename T, typename... Args>
	void log(T first, Args... args) 
	{

	}
	
};
