// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DestinyPawnData.generated.h"

/**
 * 어떤 Pawn을 생성할지, 입력은 어떤지, Ability는 어떤걸 가지고 있는지
 */
UCLASS()
class DESTINY_API UDestinyPawnData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UDestinyPawnData();
	
};
