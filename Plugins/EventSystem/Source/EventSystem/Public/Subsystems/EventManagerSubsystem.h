// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "EventManagerSubsystem.generated.h"

class UEventBase;

DECLARE_DYNAMIC_DELEGATE_OneParam(FEventReceiver, UEventBase*, _ExecutedEvent);
DECLARE_MULTICAST_DELEGATE_OneParam(FProcessEvent, UEventBase*);

/**
 * 
 */

UCLASS()
class EVENTSYSTEM_API UEventManagerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"))
	static void ExecuteEvent(UEventBase* _EventToExecute, const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static void ExecuteEventOfClass(TSubclassOf<UEventBase> _EventClass, UObject* _Outer, const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"))
	static void BindReceiverToEvent(TSubclassOf<UEventBase> _EventClass, FEventReceiver _OnEventExecuted, const UObject* WorldContextObject);

	FProcessEvent OnEventExecuted;
	
};
