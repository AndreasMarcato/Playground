// Fill out your copyright notice in the Description page of Project Settings.


#include "CggCharacterBaseGAS.h"
#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "BasicAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"

// Constructor implementation to sets default values
ACggCharacterBaseGAS::ACggCharacterBaseGAS()
{
	// Set this character to call Tick() every frame.
	// You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Add ASC
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	//Add the basic attribute set
	BasicAttributeSet = CreateDefaultSubobject<UBasicAttributeSet>(TEXT("BasicAttributeSet"));
	AbilitySystemComponent->AddAttributeSetSubobject(BasicAttributeSet);

	//Add default values, I copied them from the Character C++ base file.
	//Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(35.0f, 90.0f);

	//Don't rotate when the controller rotates. Let tjjat just affect the camera
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//Configure Character Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 5000.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 500.0f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 200.0f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;



}


// we need to initialize the ASC when we possess the character,
// and also when the player state is replicated on clients
void ACggCharacterBaseGAS::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (AbilitySystemComponent)
		AbilitySystemComponent->InitAbilityActorInfo(this, this);

	for (const auto& EachAbility : InitalAbilities)
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(EachAbility));
}

void ACggCharacterBaseGAS::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	CggPostInitializeComponents();

	AbilitySystemComponent->SetNumericAttributeBase(BasicAttributeSet->GetMaxHealthAttribute(), 200);
	AbilitySystemComponent->SetNumericAttributeBase(BasicAttributeSet->GetHealthAttribute(), 200);


}

// Called when the game starts or when spawned
void ACggCharacterBaseGAS::BeginPlay()
{
	Super::BeginPlay();

}



// we need to check if the ASC is valid when the player state is replicated
void ACggCharacterBaseGAS::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	if (AbilitySystemComponent)
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
}


// Called to bind functionality to input
void ACggCharacterBaseGAS::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Called in the BP to get the ASC for this character
UAbilitySystemComponent* ACggCharacterBaseGAS::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
