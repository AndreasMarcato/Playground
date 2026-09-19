// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "CggCharacterBaseGAS.generated.h"

UCLASS()
class PLAYGROUND_API ACggCharacterBaseGAS : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Constructor, sets default values for this character's properties
	ACggCharacterBaseGAS();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;
	virtual void PostInitializeComponents() override;

	UFUNCTION(BlueprintImplementableEvent)
	void CggPostInitializeComponents();

protected:
	// from the implemented Interface, return the ASC for this character
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	// Ability System Component for this character and Attributes
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AbilitySystem")
	TObjectPtr<class UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilitySystem")
	TArray<TSubclassOf<class UGameplayAbility>> InitalAbilities;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attribute")
	class UBasicAttributeSet* BasicAttributeSet;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when the player state is replicated
	virtual void OnRep_PlayerState() override;


};
