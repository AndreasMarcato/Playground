// Fill out your copyright notice in the Description page of Project Settings.


#include "CggInteractableBase.h"
#include "AbilitySystemComponent.h"

//We need these becasue we are using the StaticMeshComponent and ArrowComponent in our Interactable class,
// so we need to include their headers to use them. Since we are using pointers in the .h script,
// we don't need to include their headers there, but we do need to include them here in the .cpp file.
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"

//Constructor, set default values here
ACggInteractableBase::ACggInteractableBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//GAS
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	//This will establish the SM as the root component of the Interactable,
	// so that we can set its location and rotation in the world.
	InteractableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InteractableMesh"));
	RootComponent = InteractableMesh;

	//We will use this for the alignment arrow where the player will go to.
	PlayerInteractionMarker = CreateDefaultSubobject<UArrowComponent>(TEXT("PlayerInteractionMarker"));
	PlayerInteractionMarker->SetupAttachment(RootComponent);

	//Set the default location and rotation of the arrow component relative to the Interactable's mesh.
	PlayerInteractionMarker->SetRelativeLocation(FVector(80.f, 0.f, 0.f));
	PlayerInteractionMarker->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));

}

// Called when the game starts or when spawned
void ACggInteractableBase::BeginPlay()
{
	Super::BeginPlay();

	//GAS initialization
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}

}

// Called every frame
void ACggInteractableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UAbilitySystemComponent* ACggInteractableBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


