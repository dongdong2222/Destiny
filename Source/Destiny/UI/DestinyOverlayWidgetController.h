// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DestinyWidgetController.h"
#include "DestinyOverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, Health);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, MaxHealth);

struct FOnAttributeChangeData;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class DESTINY_API UDestinyOverlayWidgetController : public UDestinyWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbackToDependencies() override;
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes");
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes");
	FOnMaxHealthChangedSignature OnMaxHealthChanged;
protected:
	void HealthChagned(const FOnAttributeChangeData& Data) const;
	void MaxHealthChagned(const FOnAttributeChangeData& Data) const;
};
