// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Destiny/Character/DestinyCharacterBase.h"
#include "AbilitySystemInterface.h"
#include "DestinyCharacter.generated.h"



UCLASS()
class DESTINY_API ADestinyCharacter : public ADestinyCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADestinyCharacter();

public:	


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

protected:
	virtual void BeginPlay() override;


private:
	virtual void InitAbilityActorInfo() override;

};
