// Fill out your copyright notice in the Description page of Project Settings.


#include "DestinyOverlayWidgetController.h"
#include "AbilitySystemComponent.h"
#include "Destiny/AbilitySystem/DestinyAttributeSet.h"

void UDestinyOverlayWidgetController::BroadcastInitialValues()
{
	const UDestinyAttributeSet* DestinyAttributeSet =  CastChecked<UDestinyAttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(DestinyAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(DestinyAttributeSet->GetMaxHealth());

}

void UDestinyOverlayWidgetController::BindCallbackToDependencies()
{
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Cast<UDestinyAttributeSet>(AttributeSet)->GetHealthAttribute())
		.AddUObject(this, &ThisClass::HealthChagned);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Cast<UDestinyAttributeSet>(AttributeSet)->GetMaxHealthAttribute())
		.AddUObject(this, &ThisClass::MaxHealthChagned);
}

void UDestinyOverlayWidgetController::HealthChagned(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UDestinyOverlayWidgetController::MaxHealthChagned(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);

}
