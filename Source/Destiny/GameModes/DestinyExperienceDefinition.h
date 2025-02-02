// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DestinyExperienceDefinition.generated.h"

class ULyraPawnData;

/**
 * 
 */
UCLASS()
class DESTINY_API UDestinyExperienceDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UDestinyExperienceDefinition();

	/** The default pawn class to spawn for players */
	//@TODO: Make soft?
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
	TObjectPtr<const ULyraPawnData> DefaultPawnData;

	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
	TArray<FString> GameFeaturesToEnable;
	
};
