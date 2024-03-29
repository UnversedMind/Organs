// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/InteractionEventSubsystem.h"
#include "Controllers/InteractionController.h"

void UInteractionEventSubsystem::BindEventToClassInteraction(UInteractionController* _InteractionController, TSubclassOf<UObject> _InteractableClass, FInteractionEvent _SuccessInteractionEvent, FInteractionEvent _FailureInteractionEvent)
{
	check(_InteractionController);
	_InteractionController->OnActionTriggered.AddLambda([this, _InteractionController, _InteractableClass, _SuccessInteractionEvent, _FailureInteractionEvent](UInteractionController* _DelegateOwner, UObject* _InteractableItem, bool bSuccess)
	{
		if (_InteractableItem->GetClass()->IsChildOf(_InteractableClass) && _InteractionController == _DelegateOwner)
		{
			if (bSuccess) 
			{
				_SuccessInteractionEvent.ExecuteIfBound();
				return;
			}
			_FailureInteractionEvent.ExecuteIfBound();
		}
	});
}

void UInteractionEventSubsystem::BindEventToObjectInteraction(UInteractionController* _InteractionController, UObject* _Interactable, FInteractionEvent _SuccessInteractionEvent, FInteractionEvent _FailureInteractionEvent)
{
	check(_InteractionController);
	_InteractionController->OnActionTriggered.AddLambda([this, _InteractionController, _Interactable, _SuccessInteractionEvent, _FailureInteractionEvent](UInteractionController* _DelegateOwner, UObject* _InteractableItem, bool bSuccess)
	{
		if (_InteractableItem == _Interactable && _InteractionController == _DelegateOwner)
		{
			if (bSuccess)
			{
				_SuccessInteractionEvent.ExecuteIfBound();
				return;
			}
			_FailureInteractionEvent.ExecuteIfBound();
		}
	});
}

void UInteractionEventSubsystem::BindEventToClassStopInteraction(UInteractionController* _InteractionController, TSubclassOf<UObject> _InteractableClass, FInteractionEvent _SuccessStopInteractionEvent, FInteractionEvent _FailureStopInteractionEvent)
{
	check(_InteractionController);
	_InteractionController->OnStopActionTriggered.AddLambda([this, _InteractionController, _InteractableClass, _SuccessStopInteractionEvent, _FailureStopInteractionEvent](UInteractionController* _DelegateOwner, UObject* _InteractableItem, bool bSuccess)
	{
		if (_InteractableItem->GetClass()->IsChildOf(_InteractableClass) && _InteractionController == _DelegateOwner)
		{
			if (bSuccess) 
			{
				_SuccessStopInteractionEvent.ExecuteIfBound();
			}
			_FailureStopInteractionEvent.ExecuteIfBound();
		}
	});
}

void UInteractionEventSubsystem::BindEventToObjectStopInteraction(UInteractionController* _InteractionController, UObject* _Interactable, FInteractionEvent _SuccessStopInteractionEvent, FInteractionEvent _FailureStopInteractionEvent)
{
	check(_InteractionController);
	_InteractionController->OnStopActionTriggered.AddLambda([this, _InteractionController, _Interactable, _SuccessStopInteractionEvent, _FailureStopInteractionEvent](UInteractionController* _DelegateOwner, UObject* _InteractableItem, bool bSuccess)
	{
		if (_InteractableItem == _Interactable && _InteractionController == _DelegateOwner)
		{
			if (bSuccess)
			{
				_SuccessStopInteractionEvent.ExecuteIfBound();
			}
			_FailureStopInteractionEvent.ExecuteIfBound();
		}
	});
}

void UInteractionEventSubsystem::BindEventToClassInteractionWithReturn(UInteractionController* _InteractionController, TSubclassOf<UObject> _InteractableClass, FItemInteractionEvent _SuccessInteractionEvent, FItemInteractionEvent _FailureInteractionEvent)
{
	check(_InteractionController);
	_InteractionController->OnActionTriggered.AddLambda([this, _InteractionController, _InteractableClass, _SuccessInteractionEvent, _FailureInteractionEvent](UInteractionController* _DelegateOwner, UObject* _InteractableItem, bool bSuccess)
	{
		if (_InteractableItem->GetClass()->IsChildOf(_InteractableClass) && _InteractionController == _DelegateOwner)
		{
			if (bSuccess)
			{
				_SuccessInteractionEvent.ExecuteIfBound(_InteractableItem);
				return;
			}
			_FailureInteractionEvent.ExecuteIfBound(_InteractableItem);
		}
	});
}

void UInteractionEventSubsystem::BindEventToObjectInteractionWithReturn(UInteractionController* _InteractionController, UObject* _Interactable, FItemInteractionEvent _SuccessInteractionEvent, FItemInteractionEvent _FailureInteractionEvent)
{
	check(_InteractionController);
	_InteractionController->OnActionTriggered.AddLambda([this, _InteractionController, _Interactable, _SuccessInteractionEvent, _FailureInteractionEvent](UInteractionController* _DelegateOwner, UObject* _InteractableItem, bool bSuccess)
	{
		if (_InteractableItem == _Interactable && _InteractionController == _DelegateOwner)
		{
			if (bSuccess)
			{
				_SuccessInteractionEvent.ExecuteIfBound(_InteractableItem);
				return;
			}
			_FailureInteractionEvent.ExecuteIfBound(_InteractableItem);
		}
	});
}

void UInteractionEventSubsystem::BindEventToClassStopInteractionWithReturn(UInteractionController* _InteractionController, TSubclassOf<UObject> _InteractableClass, FItemInteractionEvent _SuccessStopInteractionEvent, FItemInteractionEvent _FailureStopInteractionEvent)
{
	check(_InteractionController);
	_InteractionController->OnStopActionTriggered.AddLambda([this, _InteractionController, _InteractableClass, _SuccessStopInteractionEvent, _FailureStopInteractionEvent](UInteractionController* _DelegateOwner, UObject* _InteractableItem, bool bSuccess)
	{
		if (_InteractableItem->GetClass()->IsChildOf(_InteractableClass) && _InteractionController == _DelegateOwner)
		{
			if (bSuccess)
			{
				_SuccessStopInteractionEvent.ExecuteIfBound(_InteractableItem);
			}
			_FailureStopInteractionEvent.ExecuteIfBound(_InteractableItem);
		}
	});
}

void UInteractionEventSubsystem::BindEventToObjectStopInteractionWithReturn(UInteractionController* _InteractionController, UObject* _Interactable, FItemInteractionEvent _SuccessStopInteractionEvent, FItemInteractionEvent _FailureStopInteractionEvent)
{
	check(_InteractionController);
	_InteractionController->OnStopActionTriggered.AddLambda([this, _InteractionController, _Interactable, _SuccessStopInteractionEvent, _FailureStopInteractionEvent](UInteractionController* _DelegateOwner, UObject* _InteractableItem, bool bSuccess)
	{
		if (_InteractableItem == _Interactable && _InteractionController == _DelegateOwner)
		{
			if (bSuccess)
			{
				_SuccessStopInteractionEvent.ExecuteIfBound(_InteractableItem);
			}
			_FailureStopInteractionEvent.ExecuteIfBound(_InteractableItem);
		}
	});
}
