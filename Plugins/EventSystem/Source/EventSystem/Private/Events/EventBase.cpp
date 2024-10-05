// Fill out your copyright notice in the Description page of Project Settings.


#include "Events/EventBase.h"

UObject* UEventBase::GetWorldContextObject()
{
    return WorldContextObject;
}

void UEventBase::SetWorldContextObject(UObject* _WorldContextObject)
{
	WorldContextObject = _WorldContextObject;
}
