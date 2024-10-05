// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/EventManagerSubsystem.h"
#include "Events/EventBase.h"

void UEventManagerSubsystem::ExecuteEvent(UEventBase* _EventToExecute, const UObject* WorldContextObject)
{
	UEventManagerSubsystem* _Subsystem = WorldContextObject->GetWorld()->GetSubsystem<UEventManagerSubsystem>();
	_Subsystem->OnEventExecuted.Broadcast(_EventToExecute);
}

void UEventManagerSubsystem::ExecuteEventOfClass(TSubclassOf<UEventBase> _EventClass, UObject* _Outer, const UObject* WorldContextObject)
{
	UEventBase* _EventToExecute = NewObject<UEventBase>(_Outer, _EventClass->StaticClass());
	UEventManagerSubsystem::ExecuteEvent(_EventToExecute, WorldContextObject);
}

void UEventManagerSubsystem::BindReceiverToEvent(TSubclassOf<UEventBase> _EventClass, FEventReceiver _OnEventExecuted, const UObject* WorldContextObject)
{
	UEventManagerSubsystem* _Subsystem = WorldContextObject->GetWorld()->GetSubsystem<UEventManagerSubsystem>();
	_Subsystem->OnEventExecuted.AddLambda([_EventClass, _OnEventExecuted](UEventBase* _EventToExecute)
		{
			if (_EventToExecute->GetClass()->IsChildOf(_EventClass)) 
			{
				_OnEventExecuted.ExecuteIfBound(_EventToExecute);
			}
		});
}
