// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "K2Node_CallFunction.h"
#include "K2Node_AddPinInterface.h"
#include "K2Node_CustomInput.generated.h"

/**
 * 
 */
UCLASS()
class ORGANMECHANICS_API UK2Node_CustomInput : public UK2Node_CallFunction, public IK2Node_AddPinInterface
{
	GENERATED_BODY()

public:

	virtual void AllocateDefaultPins() override;

	virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;

	virtual FLinearColor GetNodeTitleColor() const override;

	virtual void AddInputPin() override;

	virtual bool CanAddPin() const override;

	virtual bool CanRemovePin(const UEdGraphPin* Pin) const override;

	virtual void RemoveInputPin(UEdGraphPin* Pin) override;

	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;

	virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;

	virtual void GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;

	virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;

	virtual void SetFromFunction(const UFunction* Function) override;

private:

	UEdGraphPin* AddInputPinImpl(int32 PinIndex);

	TArray<UEdGraphPin*> GetInputPins(bool bIncludeLinks = false) const;

	bool IsAdditionalPin(UEdGraphPin* Pin);

	UEdGraphPin* GetAdditionalPin(int32 PinIndex) const;

	UPROPERTY()
	int32 NumAdditionalInputs;

};
