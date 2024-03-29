// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CharacterAttributeSet.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayEffects/GameplayEffectExtender.h"
#include "GameplayEffectExtension.h"

#define DefaultMaxWalkSpeed 300.0f
#define DefaultMaxRunSpeed 600.0f

UCharacterAttributeSet::UCharacterAttributeSet()
{
	InitHealth(DefaultHealthValue);
	InitBloodLevel(100.0f);
	InitBloodOxygen(100.0f);
}

void UCharacterAttributeSet::OnTick()
{
	UpdateHealthFromToxicity();
	UGameplayEffectExtender::ApplyModifier(GetOwningAbilitySystemComponent(), GetBloodLevelAttribute(), BloodLossRegenValue);
}

void UCharacterAttributeSet::UpdateHealthFromToxicity()
{
	if (GetBloodToxicity() > 50.0f) 
	{
		UGameplayEffectExtender::ApplyModifier(GetOwningAbilitySystemComponent(), GetHealthAttribute(), -(GetBloodToxicity() * HealthToxicityMultiplier));
	}
}

void UCharacterAttributeSet::SetMaxWalkSpeed(float _NewSpeed)
{
	MaxWalkSpeed = _NewSpeed;
	UpdateCharacterSpeed();
}

void UCharacterAttributeSet::SetIsOxygenDepleted(bool _NewIsOxygenDepleted)
{
	bIsOxygenDepleted = _NewIsOxygenDepleted;
	OnOxygenDepletionChanged.Broadcast(bIsOxygenDepleted);
}

void UCharacterAttributeSet::UpdateCharacterSpeed()
{
	float BloodLevelMultiplier = GetBloodLevel() / 100.0f;
	float newWalkSpeed = MaxWalkSpeed * BloodLevelMultiplier;

	UCharacterMovementComponent* _CMC = Cast<ACharacter>(GetOwningActor())->GetCharacterMovement();
	_CMC->MaxWalkSpeed = newWalkSpeed;
}

float UCharacterAttributeSet::GetHealth() const
{
	return FMath::Max(Health.GetCurrentValue(), 0.0f);
}

void UCharacterAttributeSet::SetHealth(float _NewHealthValue)
{
	_NewHealthValue = FMath::Clamp(_NewHealthValue, 0.0f, DefaultHealthValue);

	if (_NewHealthValue == 0.0f) 
	{
		bIsCharacterDead = true;
		CharacterDied.Broadcast();
	}

	UAbilitySystemComponent* abilitySystemComponent = GetOwningAbilitySystemComponent();
	if (ensure(abilitySystemComponent))
	{
		abilitySystemComponent->SetNumericAttributeBase(GetHealthAttribute(), _NewHealthValue);
	}
}

float UCharacterAttributeSet::GetBloodToxicity() const
{
	return FMath::Clamp(BloodToxicity.GetCurrentValue(), 0.0f, 100.0f);
}

void UCharacterAttributeSet::SetBloodToxicity(float _NewBloodToxicityValue)
{
	_NewBloodToxicityValue = FMath::Clamp(_NewBloodToxicityValue, 0.0f, 100.0f);

	UAbilitySystemComponent* abilitySystemComponent = GetOwningAbilitySystemComponent();
	if (ensure(abilitySystemComponent))
	{
		abilitySystemComponent->SetNumericAttributeBase(GetBloodToxicityAttribute(), _NewBloodToxicityValue);
	}
}

float UCharacterAttributeSet::GetBloodOxygen() const
{
	return FMath::Clamp(BloodOxygen.GetCurrentValue(), 0.0f, 100.0f);
}

void UCharacterAttributeSet::SetBloodOxygen(float _NewBloodOxygen)
{
	_NewBloodOxygen = FMath::Clamp(_NewBloodOxygen, 0.0f, 100.0f);

	if (_NewBloodOxygen == 0.0f) 
	{
		SetIsOxygenDepleted(true);
	}
	if (_NewBloodOxygen == 100.0f) 
	{
		SetIsOxygenDepleted(false);
	}

	UAbilitySystemComponent* abilitySystemComponent = GetOwningAbilitySystemComponent();
	if (ensure(abilitySystemComponent))
	{
		abilitySystemComponent->SetNumericAttributeBase(GetBloodOxygenAttribute(), _NewBloodOxygen);
	}
}

float UCharacterAttributeSet::GetBloodLevel() const
{
	return FMath::Clamp(BloodLevel.GetCurrentValue(), 0.0f, 100.0f);
}

void UCharacterAttributeSet::SetBloodLevel(float _NewBloodLevelValue)
{
	_NewBloodLevelValue = FMath::Clamp(_NewBloodLevelValue, 0.0f, 100.0f);

	UAbilitySystemComponent* abilitySystemComponent = GetOwningAbilitySystemComponent();
	if (ensure(abilitySystemComponent))
	{
		abilitySystemComponent->SetNumericAttributeBase(GetBloodLevelAttribute(), _NewBloodLevelValue);
		UpdateCharacterSpeed();
	}
}

float UCharacterAttributeSet::GetExperience() const
{
	return FMath::Max(Experience.GetCurrentValue(), 0.0f);
}

void UCharacterAttributeSet::SetExperience(float _NewExperienceValue)
{
	_NewExperienceValue = FMath::Max(_NewExperienceValue, 0.0f);

	UAbilitySystemComponent* abilitySystemComponent = GetOwningAbilitySystemComponent();
	if (ensure(abilitySystemComponent))
	{
		abilitySystemComponent->SetNumericAttributeBase(GetExperienceAttribute(), _NewExperienceValue);
	}
}

void UCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (bIsCharacterDead) 
	{
		return;
	}

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Max(GetHealth(), 0.0f));
	}

	if (Data.EvaluatedData.Attribute == GetBloodToxicityAttribute())
	{
		SetBloodToxicity(FMath::Clamp(GetBloodToxicity(), 0.0f, 100.0f));
	}

	if (Data.EvaluatedData.Attribute == GetBloodOxygenAttribute())
	{
		SetBloodOxygen(FMath::Clamp(GetBloodOxygen(), 0.0f, 100.0f));
	}

	if (Data.EvaluatedData.Attribute == GetBloodLevelAttribute())
	{
		SetBloodLevel(FMath::Clamp(GetBloodLevel(), 0.0f, 100.0f));
	}

	if (Data.EvaluatedData.Attribute == GetExperienceAttribute())
	{
		SetExperience(FMath::Max(GetExperience(), 0.0f));
	}
}
