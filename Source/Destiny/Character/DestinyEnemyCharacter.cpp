// Fill out your copyright notice in the Description page of Project Settings.


#include "DestinyEnemyCharacter.h"
#include "Destiny/AbilitySystem/DestinyAbilitySystemComponent.h"
#include "Destiny/AbilitySystem/DestinyAttributeSet.h"

ADestinyEnemyCharacter::ADestinyEnemyCharacter()
{
	//1초당 100번 update 하겠다는것(replicate하겠다는 것)
	NetUpdateFrequency = 100.0f;

	AbilitySystemComponent = CreateDefaultSubobject<UDestinyAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);



	AbilitySet = CreateDefaultSubobject<UDestinyAttributeSet>(TEXT("AbilitySet"));
}

void ADestinyEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	//Set ownerActor and avatarActor
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void ADestinyEnemyCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
