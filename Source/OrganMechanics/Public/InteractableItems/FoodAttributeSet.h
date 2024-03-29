// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "FoodAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class ORGANMECHANICS_API UFoodAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Toxicity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Healing;

public:

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UFoodAttributeSet, Toxicity);
	float GetToxicityValue() const;
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Toxicity);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Toxicity);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UFoodAttributeSet, Healing);
	float GetHealingValue() const;
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Healing);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Healing);
	
};
