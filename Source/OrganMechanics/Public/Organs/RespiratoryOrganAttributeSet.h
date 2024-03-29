// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OrganBaseAttributeSet.h"
#include "RespiratoryOrganAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class ORGANMECHANICS_API URespiratoryOrganAttributeSet : public UOrganBaseAttributeSet
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData OxygenAbsorptionLevel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float OxygenAbsorptionLevelDefaultValue = 0.005f;

public:

	virtual void OnTick() override;

	void UpdateOwnerBloodOxygen();

	virtual void PostAddAttributeSetToAbilitySystemComponent() override;

	virtual void GetUpgradeableAttributes(TArray<FGameplayAttribute>& OutAttributes) override;

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(URespiratoryOrganAttributeSet, OxygenAbsorptionLevel);
	float GetOxygenAbsorptionLevel() const;
	void SetOxygenAbsorptionLevel(float _NewOxygenAbsorptionLevelValue);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(OxygenAbsorptionLevel);

	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

};
