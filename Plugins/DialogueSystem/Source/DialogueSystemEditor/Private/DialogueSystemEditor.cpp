// Copyright Epic Games, Inc. All Rights Reserved.

#include "DialogueSystemEditor.h"
#include "Structs/DialogueStruct.h"
#include "Customisation/OptionSelectorCustomisation.h"

#define LOCTEXT_NAMESPACE "FDialogueSystemEditorModule"

void FDialogueSystemEditorModule::StartupModule()
{
	// import the PropertyEditor module...
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	// to register our custom property
	PropertyModule.RegisterCustomPropertyTypeLayout(
		// This is the name of the Struct (we can also use "MyStruct" instead)
		// this tells the property editor which is the struct property our customization will applied on.
		FDialogueOptionEffect::StaticStruct()->GetFName(),
		// this is where our MakeInstance() method is usefull
		FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FOptionSelectorCustomization::MakeInstance));

	PropertyModule.NotifyCustomizationModuleChanged();
}

void FDialogueSystemEditorModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		// unregister properties when the module is shutdown
		FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.UnregisterCustomPropertyTypeLayout("DialogueOptionEffect");

		PropertyModule.NotifyCustomizationModuleChanged();
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDialogueSystemEditorModule, DialogueSystem)