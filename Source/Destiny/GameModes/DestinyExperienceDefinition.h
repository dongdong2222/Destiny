// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DestinyExperienceDefinition.generated.h"

class UDestinyPawnData;

/**
 * 
 */
UCLASS(BlueprintType, Const)
class DESTINY_API UDestinyExperienceDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UDestinyExperienceDefinition();

	/** The default pawn class to spawn for players */
	//@TODO: Make soft?
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
	TObjectPtr<const UDestinyPawnData> DefaultPawnData;

	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
	TArray<FString> GameFeaturesToEnable;
	
};
