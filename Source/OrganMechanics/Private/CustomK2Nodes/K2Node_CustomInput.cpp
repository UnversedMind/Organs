// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomK2Nodes/K2Node_CustomInput.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "BlueprintTypePromotion.h"

#include "ToolMenu.h"
#include "Internationalization/Internationalization.h"
#include "Kismet2/WildcardNodeUtils.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "ScopedTransaction.h"
#include "UI/Bridges/MultiControlBridge.h"
#include "EdGraphSchema_K2.h"

#define LOCTEXT_NAMESPACE "CreatablePins"

void UK2Node_CustomInput::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);

	for (int32 i = 0; i < (NumAdditionalInputs); ++i)
	{
		AddInputPinImpl(i);
	}
}

void UK2Node_CustomInput::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);

	//FunctionReference.SetExternalMember(
	//	GET_FUNCTION_NAME_CHECKED(UMultiControlBridge, ExampleFunction),
	//	UExampleClass::StaticClass()
	//);
}

FLinearColor UK2Node_CustomInput::GetNodeTitleColor() const
{
	return FLinearColor(0.5f, 0.1f, 0.1f, 1.0f);
}

void UK2Node_CustomInput::AddInputPin()
{
	if (CanAddPin())
	{
		FScopedTransaction Transaction(LOCTEXT("AddPinCustomInput", "AddPin"));
		Modify();

		const FName _PinName = GetNameForAdditionalPin(NumAdditionalInputs);

		NumAdditionalInputs++;

		FWildcardNodeUtils::CreateWildcardPin(this, FName(_PinName), EGPD_Input);
	}
}

bool UK2Node_CustomInput::CanAddPin() const
{
	return true;
}

bool UK2Node_CustomInput::CanRemovePin(const UEdGraphPin* Pin) const
{
	return (
		Pin && Pin->ParentPin == nullptr &&
		INDEX_NONE != Pins.IndexOfByKey(Pin) &&
		Pin->Direction == EEdGraphPinDirection::EGPD_Input
		);
}

void UK2Node_CustomInput::RemoveInputPin(UEdGraphPin* Pin)
{
	if (CanRemovePin(Pin))
	{
		FScopedTransaction Transaction(LOCTEXT("RemovePinCustomInput", "RemovePin"));
		Modify();

		if (RemovePin(Pin)) 
		{
			--NumAdditionalInputs;

			int32 NameIndex = 0;
			const UEdGraphPin* SelfPin = FindPin(UEdGraphSchema_K2::PN_Self);

			for (int32 PinIndex = 0; PinIndex < Pins.Num(); ++PinIndex)
			{
				UEdGraphPin* LocalPin = Pins[PinIndex];

				if (LocalPin && (LocalPin->Direction != EGPD_Output) && (LocalPin != SelfPin) && LocalPin->ParentPin == nullptr
					&& IsAdditionalPin(LocalPin))
				{
					const FName PinName = GetNameForAdditionalPin(NameIndex);
					if (PinName != LocalPin->PinName)
					{
						LocalPin->Modify();
						LocalPin->PinName = PinName;
					}
					NameIndex++;
				}
			}
			FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(GetBlueprint());
		}
	}
}

void UK2Node_CustomInput::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	UClass* actionKey = GetClass();

	if (ActionRegistrar.IsOpenForRegistration(actionKey))
	{
		UBlueprintNodeSpawner* nodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(nodeSpawner != nullptr);

		ActionRegistrar.AddBlueprintAction(actionKey, nodeSpawner);
	}
}

void UK2Node_CustomInput::NotifyPinConnectionListChanged(UEdGraphPin* Pin)
{
	Super::NotifyPinConnectionListChanged(Pin);

	if (!Pin) 
	{
		return;
	}

	if (Pin->GetName() != UEdGraphSchema_K2::PN_Execute &&
		Pin->GetName() != UEdGraphSchema_K2::PN_Then)
	{
		if (Pin->LinkedTo.Num() > 0)
		{
			Pin->PinType.PinCategory = Pin->LinkedTo[0]->PinType.PinCategory;
			return;
		}
		Pin->PinType.PinCategory = UEdGraphSchema_K2::PC_Wildcard;
	}
}

void UK2Node_CustomInput::GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	Super::GetNodeContextMenuActions(Menu, Context);

	static const FName CreatablePins = FName("CreatablePins");
	static const FText CreatablePinsText = LOCTEXT("CreatablePins", "Creatable pins");

	// Add the option to remove a pin via the context menu
	if (CanRemovePin(Context->Pin))
	{
		FToolMenuSection& Section = Menu->AddSection(CreatablePins, CreatablePinsText);
		Section.AddMenuEntry(
			"RemovePin",
			LOCTEXT("RemovePin", "Remove pin"),
			LOCTEXT("RemovePinTooltip", "Remove this input pin"),
			FSlateIcon(),
			FUIAction(
				FExecuteAction::CreateUObject(const_cast<UK2Node_CustomInput*>(this), &UK2Node_CustomInput::RemoveInputPin, const_cast<UEdGraphPin*>(Context->Pin))
			)
		);
	}
	else if (CanAddPin())
	{
		FToolMenuSection& Section = Menu->AddSection(CreatablePins, CreatablePinsText);
		Section.AddMenuEntry(
			"AddPin",
			LOCTEXT("AddPin", "Add pin"),
			LOCTEXT("AddPinTooltip", "Add another input pin"),
			FSlateIcon(),
			FUIAction(
				FExecuteAction::CreateUObject(const_cast<UK2Node_CustomInput*>(this), &UK2Node_CustomInput::AddInputPin)
			)
		);
	}
}

void UK2Node_CustomInput::ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins)
{
	Super::ReallocatePinsDuringReconstruction(OldPins);

	// We need to fix up any additional pins that may have been created as a wildcard pin
	int32 AdditionalPinsFixed = 0;

	// Additional Pin creation here? Check for orphan pins here and see if we can re-create them
	for (UEdGraphPin* OldPin : OldPins)
	{
		if (ensure(OldPin))
		{
			if (IsAdditionalPin(OldPin))
			{
				if (UEdGraphPin* AddPin = GetAdditionalPin(AdditionalPinsFixed))
				{
					AddPin->PinType = OldPin->PinType;
					AddPin->DefaultValue = OldPin->DefaultValue;
					++AdditionalPinsFixed;
				}
			}

			// Copy the default value and pin type for pins without any links to preseve it
			UEdGraphPin* CurrentPin = FindPin(OldPin->GetFName(), OldPin->Direction);

			if (CurrentPin && OldPin->LinkedTo.Num() == 0 && !OldPin->DoesDefaultValueMatchAutogenerated())
			{
				CurrentPin->PinType = OldPin->PinType;
				CurrentPin->DefaultValue = OldPin->DefaultValue;
			}
		}
	}
}

void UK2Node_CustomInput::SetFromFunction(const UFunction* Function)
{

}

UEdGraphPin* UK2Node_CustomInput::GetAdditionalPin(int32 PinIndex) const
{
	const FName PinToFind = GetNameForAdditionalPin(PinIndex);

	for (UEdGraphPin* Pin : Pins)
	{
		if (Pin && Pin->PinName == PinToFind)
		{
			return Pin;
		}
	}

	return nullptr;
}

bool UK2Node_CustomInput::IsAdditionalPin(UEdGraphPin* Pin)
{
	bool ResultA = Pin->PinName != UEdGraphSchema_K2::PN_Execute;
	bool ResultB = Pin->PinName != UEdGraphSchema_K2::PN_Then;
	return ResultA && ResultB;
}

UEdGraphPin* UK2Node_CustomInput::AddInputPinImpl(int32 PinIndex)
{
	const FName NewPinName = GetNameForAdditionalPin(PinIndex);

	UEdGraphPin* NewPin = FWildcardNodeUtils::CreateWildcardPin(this, NewPinName, EGPD_Input);
	check(NewPin);

	const TArray<UEdGraphPin*> InputPins = GetInputPins(true);
	check(InputPins.Num());
	FEdGraphPinType PromotedType = FTypePromotion::GetPromotedType(InputPins);

	NewPin->PinType = PromotedType;

	return NewPin;
}

TArray<UEdGraphPin*> UK2Node_CustomInput::GetInputPins(bool bIncludeLinks) const
{
	TArray<UEdGraphPin*> InputPins;
	for (UEdGraphPin* Pin : Pins)
	{
		// Exclude split pins from this
		if (Pin && Pin->Direction == EEdGraphPinDirection::EGPD_Input && Pin->ParentPin == nullptr)
		{
			InputPins.Add(Pin);
			if (bIncludeLinks)
			{
				for (UEdGraphPin* Link : Pin->LinkedTo)
				{
					InputPins.Emplace(Link);
				}
			}
		}
	}
	return InputPins;
}
