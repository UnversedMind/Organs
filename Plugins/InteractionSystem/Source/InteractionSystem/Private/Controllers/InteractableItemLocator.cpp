// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/InteractableItemLocator.h"

UInteractableItemLocator::UInteractableItemLocator()
{
	if (GetOuter() && !OwningActor) 
	{
		OwningActor = Cast<AActor>(GetOuter());
		if (!OwningActor) 
		{
			UActorComponent* outerComp = Cast<UActorComponent>(GetOuter());
			if (!outerComp) 
			{
				return;
			}
			OwningActor = outerComp->GetOwner();
		}
	}
}

AActor* UInteractableItemLocator::GetInteractableItem(bool& _Success)
{
	_Success = false;
	return nullptr;
}

AActor* UInteractableItemLocator::GetOwningActor()
{
	return OwningActor;
}
