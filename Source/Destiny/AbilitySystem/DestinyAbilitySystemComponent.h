// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "DestinyAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class DESTINY_API UDestinyAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;
	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;
protected:
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;
};
