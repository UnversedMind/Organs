// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OrganBaseAttributeSet.h"
#include "DigestiveOrganAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class ORGANMECHANICS_API UDigestiveOrganAttributeSet : public UOrganBaseAttributeSet
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData HealthRegained;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData FoodIntake;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float HealthRegainedDefaultValue = 5.0f;

public:

	virtual void PostAddAttributeSetToAbilitySystemComponent() override;

	virtual void GetUpgradeableAttributes(TArray<FGameplayAttribute>& OutAttributes) override;

	UFUNCTION()
	void OnItemIngested(UObject* _ItemIngested);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UDigestiveOrganAttributeSet, HealthRegained);
	float GetHealthRegained() const;
	void SetHealthRegained(float _NewHealthRegainedValue);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(HealthRegained);

	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
};
