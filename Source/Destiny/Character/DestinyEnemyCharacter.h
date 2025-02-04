// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Destiny/Character/DestinyCharacter.h"
#include "DestinyEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DESTINY_API ADestinyEnemyCharacter : public ADestinyCharacter
{
	GENERATED_BODY()
public:
	ADestinyEnemyCharacter();

	virtual void BeginPlay() override;
	
};
