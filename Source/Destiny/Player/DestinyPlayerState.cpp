// Fill out your copyright notice in the Description page of Project Settings.


#include "DestinyPlayerState.h"
#include "Destiny/AbilitySystem/DestinyAbilitySystemComponent.h"
#include "Destiny/AbilitySystem/DestinyAttributeSet.h"

ADestinyPlayerState::ADestinyPlayerState()
{
	//1초당 100번 update 하겠다는것(replicate하겠다는 것)
	NetUpdateFrequency = 100.0f;

	AbilitySystemComponent = CreateDefaultSubobject<UDestinyAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);


	AbilitySet = CreateDefaultSubobject<UDestinyAttributeSet>(TEXT("AbilitySet"));
}

UAbilitySystemComponent* ADestinyPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
