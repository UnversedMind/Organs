// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayEffects/GameplayEffectExtender.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

void UGameplayEffectExtender::AddModifier(FGameplayAttribute _NewAttribute, float _AttributeFloat)
{
	FGameplayModifierInfo newModifier;
	newModifier.Attribute = _NewAttribute;
	FGameplayEffectModifierMagnitude modifierMag = FGameplayEffectModifierMagnitude(_AttributeFloat);
	newModifier.ModifierMagnitude = modifierMag;
	Modifiers.Add(newModifier);
}

void UGameplayEffectExtender::ApplyModifier(UAbilitySystemComponent* _AbilitySystemComponent, FGameplayAttribute _NewAttribute, float _AttributeFloat)
{
	TObjectPtr<UGameplayEffectExtender> newGameplayEffect = NewObject<UGameplayEffectExtender>(Cast<UObject>(_AbilitySystemComponent));
	newGameplayEffect.Get()->AddModifier(_NewAttribute, _AttributeFloat);
	newGameplayEffect->DurationPolicy;
	const FGameplayEffectSpecHandle gameplayEffectHandle = UAbilitySystemBlueprintLibrary::MakeSpecHandle(newGameplayEffect, _AbilitySystemComponent->GetOwner(), _AbilitySystemComponent->GetOwner(), 1.0f);
	_AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*gameplayEffectHandle.Data.Get());
}
