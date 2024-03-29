// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "OrganBaseAttributeSet.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, DefaultToInstanced, EditInlineNew)
class ORGANMECHANICS_API UOrganBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

private:

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxOrganHealth;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData OrganHealth;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData OrganDamageOnUse;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData BloodLossOnUse;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"))
	float MaxOrganHealthDefaultValue = 100.0f;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float BloodLossOnUseDefaultValue = 5.0f;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float OrganDamageOnUseDefaultValue = 0.1f;

protected:

	UAbilitySystemComponent* GetParentActorAbilitySystemComponent();

	const class UCharacterAttributeSet* GetCharacterAttributeSet();

public:

	UOrganBaseAttributeSet();

	virtual void PostAddAttributeSetToAbilitySystemComponent();

	virtual void OnOrganUsed();

	void UpdateOrganHealth();
	void UpdateOwnerBloodLoss();

	bool WouldOrganHealthBeLessThanZeroOnUse();

	virtual void OnTick();

	UFUNCTION(BlueprintPure)
	virtual void GetUpgradeableAttributes(TArray<FGameplayAttribute>& OutAttributes);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UOrganBaseAttributeSet, OrganHealth);
	float GetOrganHealth() const;
	void SetOrganHealth(float _NewHealthValue);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(OrganHealth);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UOrganBaseAttributeSet, MaxOrganHealth);
	float GetMaxOrganHealth() const;
	GAMEPLAYATTRIBUTE_VALUE_SETTER(MaxOrganHealth);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MaxOrganHealth);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UOrganBaseAttributeSet, BloodLossOnUse);
	float GetBloodLossOnUse() const;
	GAMEPLAYATTRIBUTE_VALUE_SETTER(BloodLossOnUse);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(BloodLossOnUse);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UOrganBaseAttributeSet, OrganDamageOnUse);
	float GetOrganDamageOnUse() const;
	void SetOrganDamageOnUse(float _NewOrganDamageOnUseValue);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(OrganDamageOnUse);

	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
};
