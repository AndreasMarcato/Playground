// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "CggInteractableBase.generated.h"

//Forward Declarations, we need these to avoid circular dependencies and reduce compile times,
// so we can use pointers or references to these classes without needing their full definitions here.
// the #include is done in the .cpp file instead.
class UAbilitySystemComponent;
class UComponents;
class UArrowComponent;

UCLASS()
class PLAYGROUND_API ACggInteractableBase : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	//Constructor
	ACggInteractableBase();

	UFUNCTION(BlueprintCallable, Category = "Interactable | Alignment")
	UArrowComponent* GetPlayerInteractionMarker() const { return PlayerInteractionMarker; }

	//GAS, this function can be overridden only if you add the interface extension in the class
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//GAS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interactable | GAS", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	//Variables we need to set up the Interactable's mesh and the marker for player interaction
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interactable | Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> InteractableMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interactable | Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UArrowComponent> PlayerInteractionMarker;

	//Data containers for the Interactable's Gameplay Tags and the Animation Montage
	// to play when the player interacts with it.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactable | Data")
	FGameplayTagContainer InteractionDefaultTags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactable | Data")
	TObjectPtr<UAnimMontage> PlayerInteractionMontage;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
