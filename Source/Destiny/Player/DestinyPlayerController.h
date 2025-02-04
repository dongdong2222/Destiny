// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DestinyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DESTINY_API ADestinyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ADestinyPlayerController();

protected:
	virtual void AcknowledgePossession(APawn* pawn) override;

	
};
