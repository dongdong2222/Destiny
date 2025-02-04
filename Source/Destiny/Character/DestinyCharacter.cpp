// Fill out your copyright notice in the Description page of Project Settings.


#include "DestinyCharacter.h"
#include "Destiny/AbilitySystem/DestinyAbilitySystemComponent.h"
#include "Destiny/Player/DestinyPlayerState.h"

// Sets default values
ADestinyCharacter::ADestinyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADestinyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADestinyCharacter::InitAbilityActorInfo()
{
	ADestinyPlayerState* DestinyPlayerState = GetPlayerState<ADestinyPlayerState>();
	check(DestinyPlayerState);
	DestinyPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(DestinyPlayerState, this);
	AbilitySystemComponent = DestinyPlayerState->GetAbilitySystemComponent();
	AbilitySet = DestinyPlayerState->GetAbilitySet();
}

void ADestinyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	//init ability actor info for the Server
	InitAbilityActorInfo();
}

void ADestinyCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	//init ability actor info for the client
	InitAbilityActorInfo();
}


UAbilitySystemComponent* ADestinyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called to bind functionality to input
void ADestinyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

