// Fill out your copyright notice in the Description page of Project Settings.


#include "Organs/RespiratoryOrganAttributeSet.h"
#include "GameplayEffects/GameplayEffectExtender.h"
#include "Characters/CharacterAttributeSet.h"
#include "GameplayEffectExtension.h"

void URespiratoryOrganAttributeSet::OnTick()
{
    Super::OnTick();
    UpdateOwnerBloodOxygen();
}

void URespiratoryOrganAttributeSet::UpdateOwnerBloodOxygen()
{
    UGameplayEffectExtender::ApplyModifier(GetParentActorAbilitySystemComponent(), GetCharacterAttributeSet()->GetBloodOxygenAttribute(), GetOxygenAbsorptionLevel()*(GetOrganHealth() / GetMaxOrganHealth()));
}

void URespiratoryOrganAttributeSet::PostAddAttributeSetToAbilitySystemComponent()
{
    InitOxygenAbsorptionLevel(OxygenAbsorptionLevelDefaultValue);
}

void URespiratoryOrganAttributeSet::GetUpgradeableAttributes(TArray<FGameplayAttribute>& OutAttributes)
{
    Super::GetUpgradeableAttributes(OutAttributes);
    OutAttributes.Push(GetOxygenAbsorptionLevelAttribute());
}

float URespiratoryOrganAttributeSet::GetOxygenAbsorptionLevel() const
{
	return FMath::Max(OxygenAbsorptionLevel.GetCurrentValue(), 0.0f);
}

void URespiratoryOrganAttributeSet::SetOxygenAbsorptionLevel(float _NewOxygenAbsorptionLevelValue)
{
    _NewOxygenAbsorptionLevelValue = FMath::Max(_NewOxygenAbsorptionLevelValue, 0.0f);

    UAbilitySystemComponent* abilitySystemComponent = GetOwningAbilitySystemComponent();
    if (ensure(abilitySystemComponent))
    {
        abilitySystemComponent->SetNumericAttributeBase(GetOxygenAbsorptionLevelAttribute(), _NewOxygenAbsorptionLevelValue);
    }
}

void URespiratoryOrganAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetOxygenAbsorptionLevelAttribute())
    {
        SetOxygenAbsorptionLevel(FMath::Max(GetOxygenAbsorptionLevel(), 0.0f));
    }
}
