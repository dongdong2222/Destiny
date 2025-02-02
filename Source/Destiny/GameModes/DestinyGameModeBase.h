// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DestinyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DESTINY_API ADestinyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

protected:
	void HandleMatchAssignmentIfNotExpectingOne();
	void OnMatchAssignmentGiven(FPrimaryAssetId ExperienceId, const FString& ExperienceIdSource);
};
