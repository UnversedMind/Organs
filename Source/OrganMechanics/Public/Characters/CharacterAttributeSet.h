// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CharacterAttributeSet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateOxygenDepleted, bool, _IsOxygenDepleted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCharacterDead);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, DefaultToInstanced, EditInlineNew)
class ORGANMECHANICS_API UCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

private:

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData BloodToxicity;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData BloodOxygen;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData BloodLevel;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Experience;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float DefaultHealthValue = 100.0f;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float BloodLossRegenValue = 0.05f;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float HealthToxicityMultiplier = 0.05f;

	bool bIsCharacterDead;

	bool bIsOxygenDepleted;

	float MaxWalkSpeed;

public:

	UCharacterAttributeSet();

	void OnTick();

	void UpdateHealthFromToxicity();

	void SetMaxWalkSpeed(float _NewSpeed);

	UFUNCTION(BlueprintPure)
	bool GetIsOxygenDepleted() 
	{
		return bIsOxygenDepleted;
	}

	void SetIsOxygenDepleted(bool _NewIsOxygenDepleted);

	void UpdateCharacterSpeed();

	UPROPERTY(BlueprintAssignable)
	FCharacterDead CharacterDied;

	UPROPERTY(BlueprintAssignable)
	FUpdateOxygenDepleted OnOxygenDepletionChanged;

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UCharacterAttributeSet, Health);
	float GetHealth() const;
	void SetHealth(float _NewHealthValue);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Health);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UCharacterAttributeSet, BloodToxicity);
	float GetBloodToxicity() const;
	void SetBloodToxicity(float _NewBloodToxicityValue);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(BloodToxicity);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UCharacterAttributeSet, BloodOxygen);
	float GetBloodOxygen() const;
	void SetBloodOxygen(float _NewBloodOxygen);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(BloodOxygen);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UCharacterAttributeSet, BloodLevel);
	float GetBloodLevel() const;
	void SetBloodLevel(float _NewBloodLevelValue);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(BloodLevel);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UCharacterAttributeSet, Experience);
	float GetExperience() const;
	void SetExperience(float _NewExperienceValue);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Experience);

	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
};
