// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OrganBaseAttributeSet.h"
#include "SensoryOrganAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class ORGANMECHANICS_API USensoryOrganAttributeSet : public UOrganBaseAttributeSet
{
	GENERATED_BODY()

private:

	//TODO: Sensory Loss currently has no effect, needs to be implemented
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData SensoryLoss;

public:

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(USensoryOrganAttributeSet, SensoryLoss);
	float GetSensoryLoss() const;
	void SetSensoryLoss(float _NewSensoryLossValue);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(SensoryLoss);

	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
};
