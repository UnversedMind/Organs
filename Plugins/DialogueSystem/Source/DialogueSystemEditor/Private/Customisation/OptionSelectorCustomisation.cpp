// Fill out your copyright notice in the Description page of Project Settings.


#include "Customisation/OptionSelectorCustomisation.h"
#include "SlateBasics.h"
#include "Structs/DialogueStruct.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "PropertyHandle.h"
#include "IDetailChildrenBuilder.h"

#define LOCTEXT_NAMESPACE "DialogueSystemEditor"

TSharedRef<IPropertyTypeCustomization> FOptionSelectorCustomization::MakeInstance()
{
	return MakeShareable(new FOptionSelectorCustomization);
}

void FOptionSelectorCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	HeaderRow.NameContent()[StructPropertyHandle->CreatePropertyNameWidget()];
}

void FOptionSelectorCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	if (!StructPropertyHandle->IsValidHandle())
	{
		return;
	}

	TSharedPtr<IPropertyHandle> FunctionTypePropertyHandle =
		StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDialogueOptionEffect, FunctionType));
	TSharedPtr<IPropertyHandle> CharacterPropertyHandle =
		StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDialogueOptionEffect, CharacterName));
	TSharedPtr<IPropertyHandle> AttributePropertyHandle =
		StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDialogueOptionEffect, AttributeToAffect));
	TSharedPtr<IPropertyHandle> ValuePropertyHandle = 
		StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDialogueOptionEffect, Value));
	TSharedPtr<IPropertyHandle> DTPropertyHandle =
		StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FDialogueOptionEffect, DataTableToImport));

	// and check them before using them
	check(FunctionTypePropertyHandle.IsValid() && CharacterPropertyHandle.IsValid() && 
		AttributePropertyHandle.IsValid() && ValuePropertyHandle.IsValid()
	&& DTPropertyHandle.IsValid());

	FunctionTypePropertyHandle->SetOnPropertyValueChanged(
		FSimpleDelegate::CreateSP(this, &FOptionSelectorCustomization::OnTypeChanged, FunctionTypePropertyHandle));

	OnTypeChanged(FunctionTypePropertyHandle);

#if WITH_EDITOR

	FString _FunctionValue;
	FunctionTypePropertyHandle->GetValueAsDisplayString(_FunctionValue);

	StructBuilder.AddCustomRow(LOCTEXT("DialogueOptionEffectRow", "DialogueOptionEffect"))
		[
			SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(EVerticalAlignment::VAlign_Center)
				.Padding(0, 0, 0, 0)
				[
					FunctionTypePropertyHandle->CreatePropertyValueWidget()
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(EVerticalAlignment::VAlign_Center)
				.Padding(5, 0)
				[
					SNew(STextBlock)
						.Text(LOCTEXT(" ", " "))
						.Font(IDetailLayoutBuilder::GetDetailFontBold())
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(EVerticalAlignment::VAlign_Center)
				[
					CharacterPropertyHandle->CreatePropertyValueWidget()
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(EVerticalAlignment::VAlign_Center)
				.Padding(5, 0)
				[
					SNew(STextBlock)
						.Text(LOCTEXT("'s ", "'s "))
						.Font(IDetailLayoutBuilder::GetDetailFontBold())
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(EVerticalAlignment::VAlign_Center)
				[
					AttributePropertyHandle->CreatePropertyValueWidget()
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(EVerticalAlignment::VAlign_Center)
				.Padding(5, 0)
				[
					SNew(STextBlock)
						.Text(MakeAttributeLambda([this] {return TextValue; }))
						.Font(IDetailLayoutBuilder::GetDetailFontBold())
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(EVerticalAlignment::VAlign_Center)
				[
					ValuePropertyHandle->CreatePropertyValueWidget()
				]
		];
	StructBuilder.AddCustomRow(LOCTEXT("DialogueOptionEffectRow2", "DialogueOptionEffect2"))
		[
			SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(EVerticalAlignment::VAlign_Center)
				.Padding(5, 0)
				[
					SNew(STextBlock)
						.Text(LOCTEXT("Insert ", "Insert "))
						.Font(IDetailLayoutBuilder::GetDetailFontBold())
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(EVerticalAlignment::VAlign_Center)
				[
					DTPropertyHandle->CreatePropertyValueWidget()
				]
		];

#endif
}

void FOptionSelectorCustomization::OnTypeChanged(TSharedPtr<IPropertyHandle> TypePropertyHandle)
{
#if WITH_EDITOR
	TextValue = LOCTEXT(" by ", " by ");
	FString _FunctionValue;
	TypePropertyHandle->GetValueAsDisplayString(_FunctionValue);

	if (_FunctionValue == "Set")
	{
		TextValue = LOCTEXT(" to ", " to ");
	}
#endif
}

#undef LOCTEXT_NAMESPACE