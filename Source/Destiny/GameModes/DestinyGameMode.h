// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DestinyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DESTINY_API ADestinyGameMode : public AGameStateBase
{
	GENERATED_BODY()
public:
	ADestinyGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//AActor interface 
	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

	//AGameStateBase interface
	virtual void AddPlayerState(APlayerState* PlayerState) override;
	virtual void RemovePlayerState(APlayerState* PlayerState) override;
	//virtual void SeamlessTravelTransitionCheckpoint(bool bToTransitionMap) override;

	//AbilitySystemInterface


};
