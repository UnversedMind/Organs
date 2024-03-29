// Fill out your copyright notice in the Description page of Project Settings.


#include "Organs/OrganBaseAttributeSet.h"
#include "Characters/CharacterAttributeSet.h"
#include "AbilitySystemGlobals.h"
#include "GameplayEffects/GameplayEffectExtender.h"
#include "GameplayEffectExtension.h"

UAbilitySystemComponent* UOrganBaseAttributeSet::GetParentActorAbilitySystemComponent()
{
    return UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwningActor()->GetAttachParentActor());
}

const UCharacterAttributeSet* UOrganBaseAttributeSet::GetCharacterAttributeSet()
{
    UAbilitySystemComponent* _ASC = GetParentActorAbilitySystemComponent();
    return Cast<UCharacterAttributeSet>(_ASC->GetAttributeSet(UCharacterAttributeSet::StaticClass()));
}

UOrganBaseAttributeSet::UOrganBaseAttributeSet()
{
    InitMaxOrganHealth(MaxOrganHealthDefaultValue);
    InitOrganHealth(MaxOrganHealthDefaultValue);
    InitOrganDamageOnUse(OrganDamageOnUseDefaultValue);
    InitBloodLossOnUse(BloodLossOnUseDefaultValue);
}

void UOrganBaseAttributeSet::PostAddAttributeSetToAbilitySystemComponent()
{
}

void UOrganBaseAttributeSet::OnOrganUsed()
{
    UpdateOrganHealth();
    UpdateOwnerBloodLoss();
}

void UOrganBaseAttributeSet::UpdateOrganHealth()
{
    float organDamage = GetMaxOrganHealth() * GetOrganDamageOnUse() * -1;
    UGameplayEffectExtender::ApplyModifier(GetOwningAbilitySystemComponent(), GetOrganHealthAttribute(), organDamage);
}

void UOrganBaseAttributeSet::UpdateOwnerBloodLoss()
{
    UGameplayEffectExtender::ApplyModifier(GetParentActorAbilitySystemComponent(), GetCharacterAttributeSet()->GetBloodLevelAttribute(), -GetBloodLossOnUse());
}

bool UOrganBaseAttributeSet::WouldOrganHealthBeLessThanZeroOnUse()
{
    float organDamage = GetMaxOrganHealth() * GetOrganDamageOnUse();
    if ((GetOrganHealth() - organDamage) < 0) 
    {
        return true;
    }
    return false;
}

void UOrganBaseAttributeSet::OnTick()
{
    UGameplayEffectExtender::ApplyModifier(GetOwningAbilitySystemComponent(), GetOrganHealthAttribute(), 0.05f);
}

void UOrganBaseAttributeSet::GetUpgradeableAttributes(TArray<FGameplayAttribute>& OutAttributes)
{
    OutAttributes.Push(GetMaxOrganHealthAttribute());
    OutAttributes.Push(GetBloodLossOnUseAttribute());
    OutAttributes.Push(GetOrganDamageOnUseAttribute());
}

float UOrganBaseAttributeSet::GetOrganHealth() const
{
	return FMath::Clamp(OrganHealth.GetCurrentValue(), 0.0f, GetMaxOrganHealth());
}

void UOrganBaseAttributeSet::SetOrganHealth(float _NewHealthValue)
{
    _NewHealthValue = FMath::Clamp(_NewHealthValue, 0.0f, GetMaxOrganHealth());

    UAbilitySystemComponent* abilitySystemComponent = GetOwningAbilitySystemComponent();
    if (ensure(abilitySystemComponent))
    {
        abilitySystemComponent->SetNumericAttributeBase(GetOrganHealthAttribute(), _NewHealthValue);
    }
}

float UOrganBaseAttributeSet::GetMaxOrganHealth() const
{
    return MaxOrganHealth.GetCurrentValue();
}

float UOrganBaseAttributeSet::GetBloodLossOnUse() const
{
	return FMath::Max(BloodLossOnUse.GetCurrentValue(), 0.0f);
}

float UOrganBaseAttributeSet::GetOrganDamageOnUse() const
{
    return FMath::Max(OrganDamageOnUse.GetCurrentValue(), 0.0f);
}

void UOrganBaseAttributeSet::SetOrganDamageOnUse(float _NewOrganDamageOnUseValue)
{
    _NewOrganDamageOnUseValue = FMath::Max(_NewOrganDamageOnUseValue, 0.0f);

    UAbilitySystemComponent* abilitySystemComponent = GetOwningAbilitySystemComponent();
    if (ensure(abilitySystemComponent))
    {
        abilitySystemComponent->SetNumericAttributeBase(GetOrganDamageOnUseAttribute(), _NewOrganDamageOnUseValue);
    }
}

void UOrganBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetOrganHealthAttribute())
    {
        SetOrganHealth(FMath::Max(GetOrganHealth(), 0.0f));
    }

    if (Data.EvaluatedData.Attribute == GetOrganDamageOnUseAttribute()) 
    {
        SetOrganDamageOnUse(FMath::Max(GetOrganDamageOnUse(), 0.0f));
    }

    if (Data.EvaluatedData.Attribute == GetBloodLossOnUseAttribute())
    {
        SetBloodLossOnUse(FMath::Max(GetBloodLossOnUse(), 0.0f));
    }
}
