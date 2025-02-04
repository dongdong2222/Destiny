// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GameStateComponent.h"
//#include "LoadingProcess"
#include "DestinyExperienceManagerComponent.generated.h"

class UDestinyExperienceDefinition;

enum class EDestinyExperienceLoadState
{
	Unloaded,
	Loading,
	LoadingGameFeatures,
	LoadingChaosTestingDelay,
	ExecutingActions,
	Loaded,
	Deactivating
};



/**
 * TODO : Implement LoadingProcessInterface
 */
UCLASS()
class DESTINY_API UDestinyExperienceManagerComponent : public UGameStateComponent
{
	GENERATED_BODY()
public:
	UDestinyExperienceManagerComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//UActorComponent interface
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void SetCurrentExperience(FPrimaryAssetId ExperienceId);

private:
	void StartExperienceLoad();
private:
	UPROPERTY()
	TObjectPtr<const UDestinyExperienceDefinition> CurrentExperience;
	EDestinyExperienceLoadState LoadState = EDestinyExperienceLoadState::Unloaded;
	
};
