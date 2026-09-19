// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicAttributeSet.h"
#include "Net/UnrealNetwork.h"

//The constructor with default values.
//Anytime you create a new attribute, you must set the default here.
UBasicAttributeSet::UBasicAttributeSet()
{
	MaxHealth = 200.0f;
	Health = 100.0f;
	MaxStamina = 100.0f;
	Stamina = 50.0f;
}

//Same here, anytime you create a new attribute,
// you must use the DOREPLIFETIME_CONDITION_NOTIFY macro to replicate it.
void UBasicAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UBasicAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBasicAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBasicAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBasicAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
}
