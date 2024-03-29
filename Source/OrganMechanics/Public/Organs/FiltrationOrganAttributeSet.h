// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OrganBaseAttributeSet.h"
#include "FiltrationOrganAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class ORGANMECHANICS_API UFiltrationOrganAttributeSet : public UOrganBaseAttributeSet
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData FilteringLevel;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float FilteringLevelDefaultValue = 0.008f;

public:

	virtual void PostAddAttributeSetToAbilitySystemComponent() override;

	virtual void OnTick() override;

	void UpdateOwnerBloodToxicity();

	virtual void GetUpgradeableAttributes(TArray<FGameplayAttribute>& OutAttributes) override;

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UFiltrationOrganAttributeSet, FilteringLevel);
	float GetFilteringLevel() const;
	void SetFilteringLevel(float _NewFilteringLevelValue);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(FilteringLevel);

	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
};
