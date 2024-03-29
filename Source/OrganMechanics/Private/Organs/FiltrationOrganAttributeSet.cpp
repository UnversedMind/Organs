// Fill out your copyright notice in the Description page of Project Settings.


#include "Organs/FiltrationOrganAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffects/GameplayEffectExtender.h"
#include "Characters/CharacterAttributeSet.h"

void UFiltrationOrganAttributeSet::PostAddAttributeSetToAbilitySystemComponent()
{
    FilteringLevel.SetBaseValue(FilteringLevelDefaultValue);
    FilteringLevel.SetCurrentValue(FilteringLevelDefaultValue);
}

void UFiltrationOrganAttributeSet::OnTick()
{
    Super::OnTick();
    UpdateOwnerBloodToxicity();
}

void UFiltrationOrganAttributeSet::UpdateOwnerBloodToxicity()
{
    UGameplayEffectExtender::ApplyModifier(GetParentActorAbilitySystemComponent(), GetCharacterAttributeSet()->GetBloodToxicityAttribute(), -GetFilteringLevel()*(GetOrganHealth()/GetMaxOrganHealth()));
}

void UFiltrationOrganAttributeSet::GetUpgradeableAttributes(TArray<FGameplayAttribute>& OutAttributes)
{
    Super::GetUpgradeableAttributes(OutAttributes);
    OutAttributes.Push(GetFilteringLevelAttribute());
}

float UFiltrationOrganAttributeSet::GetFilteringLevel() const
{
    return FMath::Max(FilteringLevel.GetCurrentValue(), 0.0f);
}

void UFiltrationOrganAttributeSet::SetFilteringLevel(float _NewFilteringLevelValue)
{
    _NewFilteringLevelValue = FMath::Max(_NewFilteringLevelValue, 0.0f);

    UAbilitySystemComponent* abilitySystemComponent = GetOwningAbilitySystemComponent();
    if (ensure(abilitySystemComponent))
    {
        abilitySystemComponent->SetNumericAttributeBase(GetFilteringLevelAttribute(), _NewFilteringLevelValue);
    }
}

void UFiltrationOrganAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetFilteringLevelAttribute())
    {
        SetFilteringLevel(FMath::Max(GetFilteringLevel(), 0.0f));
    }
}