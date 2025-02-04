// Fill out your copyright notice in the Description page of Project Settings.


#include "DestinyGameMode.h"

ADestinyGameMode::ADestinyGameMode(const FObjectInitializer& ObjectInitializer)/* : Super(ObjectInitializer)*/
{
}

void ADestinyGameMode::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void ADestinyGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void ADestinyGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ADestinyGameMode::Tick(float DeltaTime)
{
}

void ADestinyGameMode::AddPlayerState(APlayerState* PlayerState)
{
	Super::AddPlayerState(PlayerState);

}

void ADestinyGameMode::RemovePlayerState(APlayerState* PlayerState)
{
	Super::RemovePlayerState(PlayerState);
}

//void ADestinyGameMode::SeamlessTravelTransitionCheckpoint(bool bToTransitionMap)
//{
//}
