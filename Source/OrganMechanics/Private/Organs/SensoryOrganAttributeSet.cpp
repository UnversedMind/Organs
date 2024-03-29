// Fill out your copyright notice in the Description page of Project Settings.


#include "Organs/SensoryOrganAttributeSet.h"
#include "GameplayEffectExtension.h"

float USensoryOrganAttributeSet::GetSensoryLoss() const
{
    return FMath::Max(SensoryLoss.GetCurrentValue(), 0.0f);
}

void USensoryOrganAttributeSet::SetSensoryLoss(float _NewSensoryLossValue)
{
    _NewSensoryLossValue = FMath::Max(_NewSensoryLossValue, 0.0f);

    UAbilitySystemComponent* abilitySystemComponent = GetOwningAbilitySystemComponent();
    if (ensure(abilitySystemComponent))
    {
        abilitySystemComponent->SetNumericAttributeBase(GetSensoryLossAttribute(), _NewSensoryLossValue);
    }
}

void USensoryOrganAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetSensoryLossAttribute())
    {
        SetSensoryLoss(FMath::Max(GetSensoryLoss(), 0.0f));
    }
}
