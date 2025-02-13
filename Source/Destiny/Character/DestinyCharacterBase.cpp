// Fill out your copyright notice in the Description page of Project Settings.


#include "DestinyCharacterBase.h"

// Sets default values
ADestinyCharacterBase::ADestinyCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

UAbilitySystemComponent* ADestinyCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


void ADestinyCharacterBase::InitAbilityActorInfo()
{
}



