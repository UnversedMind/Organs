// Fill out your copyright notice in the Description page of Project Settings.


#include "Organs/DigestiveOrganAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Subsystems/InteractionEventSubsystem.h"
#include "Controllers/InteractionController.h"
#include "GameplayEffects/GameplayEffectExtender.h"
#include "Characters/CharacterAttributeSet.h"
#include "AbilitySystemGlobals.h"
#include "InteractableItems/FoodAttributeSet.h"
#include "InteractableItems/Food.h"

void UDigestiveOrganAttributeSet::PostAddAttributeSetToAbilitySystemComponent()
{
    HealthRegained.SetBaseValue(HealthRegainedDefaultValue);
    HealthRegained.SetCurrentValue(HealthRegainedDefaultValue);

    UInteractionEventSubsystem* interactionEventSubsystem = GetWorld()->GetSubsystem<UInteractionEventSubsystem>();
    UInteractionController* interactionController = GetOwningActor()->GetAttachParentActor()->GetComponentByClass<UInteractionController>();
    FItemInteractionEvent successEvent;
    successEvent.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(UDigestiveOrganAttributeSet, OnItemIngested));
    FItemInteractionEvent failureEvent;
    interactionEventSubsystem->BindEventToClassInteractionWithReturn(interactionController, AFood::StaticClass(), successEvent, failureEvent);
}

void UDigestiveOrganAttributeSet::GetUpgradeableAttributes(TArray<FGameplayAttribute>& OutAttributes)
{
    Super::GetUpgradeableAttributes(OutAttributes);
    OutAttributes.Push(GetHealthRegainedAttribute());
}

void UDigestiveOrganAttributeSet::OnItemIngested(UObject* _ItemIngested)
{
    AActor* actorIngested = Cast<AActor>(_ItemIngested);
    UAbilitySystemComponent* _ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(actorIngested);
    const UFoodAttributeSet* foodAttributeSet = Cast<UFoodAttributeSet>(_ASC->GetAttributeSet(UFoodAttributeSet::StaticClass()));
    UGameplayEffectExtender::ApplyModifier(GetParentActorAbilitySystemComponent(), GetCharacterAttributeSet()->GetHealthAttribute(), GetHealthRegained()*foodAttributeSet->GetHealingValue() * (GetOrganHealth() / GetMaxOrganHealth()));
}

float UDigestiveOrganAttributeSet::GetHealthRegained() const
{
	return FMath::Max(HealthRegained.GetCurrentValue(), 0.0f);
}

void UDigestiveOrganAttributeSet::SetHealthRegained(float _NewHealthRegainedValue)
{
    _NewHealthRegainedValue = FMath::Max(_NewHealthRegainedValue, 0.0f);

    UAbilitySystemComponent* abilitySystemComponent = GetOwningAbilitySystemComponent();
    if (ensure(abilitySystemComponent))
    {
        abilitySystemComponent->SetNumericAttributeBase(GetHealthRegainedAttribute(), _NewHealthRegainedValue);
    }
}

void UDigestiveOrganAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetHealthRegainedAttribute())
    {
        SetHealthRegained(FMath::Max(GetHealthRegained(), 0.0f));
    }
}
