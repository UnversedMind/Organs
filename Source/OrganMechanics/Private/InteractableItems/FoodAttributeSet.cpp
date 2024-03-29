// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableItems/FoodAttributeSet.h"

float UFoodAttributeSet::GetToxicityValue() const
{
	return FMath::Max(Toxicity.GetCurrentValue(), 0.0f);
}

float UFoodAttributeSet::GetHealingValue() const 
{
	return FMath::Max(Healing.GetCurrentValue(), 0.0f);
}