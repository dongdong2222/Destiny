// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DestinyUserFacingExperience.generated.h"

class UCommonSession_HostSessionRequest;

/**
 * 모드의 기본단위
 */
UCLASS()
class DESTINY_API UDestinyUserFacingExperience : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	/** The specific map to load */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Experience, meta = (AllowedTypes = "Map"))
	FPrimaryAssetId MapID;

	/** The gameplay experience to load */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Experience, meta = (AllowedTypes = "DestinyExperienceDefinition"))
	FPrimaryAssetId ExperienceID;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure=false, meta=(Worldcontext = "WorldContextObject"))
	UCommonSession_HostSessionRequest* CreateHostingRequest(const UObject* WorldContextObject) const;
	
};
