// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtender.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class ORGANMECHANICS_API UGameplayEffectExtender : public UGameplayEffect
{
	GENERATED_BODY()

public:

	//Adds a new modifier based on a GameplayAttribute, and an amount to alter the attribute by
	UFUNCTION(BlueprintCallable)
	void AddModifier(FGameplayAttribute _NewAttribute, float _AttributeFloat);

	//Applies an instant modifier - suitable for when the GameplayAttribute needs to be modified by a specific
	//amount
	UFUNCTION(BlueprintCallable)
	static void ApplyModifier(UAbilitySystemComponent* _AbilitySystemComponent,  FGameplayAttribute _NewAttribute, float _AttributeFloat);
	
};
