// Fill out your copyright notice in the Description page of Project Settings.


#include "Bridges/PropertyBridges/PropertyBridge.h"

UPropertyBridge* UPropertyBridge::GetAs(TSubclassOf<UPropertyBridge> _Class, bool& _Success)
{
    _Success = this->GetClass()->IsChildOf(_Class);
    return this;
}
