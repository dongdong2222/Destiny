// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Destiny/Character/DestinyCharacterBase.h"
#include "DestinyEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DESTINY_API ADestinyEnemyCharacter : public ADestinyCharacterBase
{
	GENERATED_BODY()
public:
	ADestinyEnemyCharacter();

	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
};
