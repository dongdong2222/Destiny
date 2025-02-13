// Fill out your copyright notice in the Description page of Project Settings.


#include "DestinyOverlayWidgetController.h"
#include "AbilitySystemComponent.h"
#include "Destiny/AbilitySystem/DestinyAbilitySystemComponent.h"
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

	Cast<UDestinyAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& TagContainer) {
			for (const FGameplayTag& Tag : TagContainer)
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("GE Tag : %s"), *Tag.ToString()));
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Attribute.Message"));

				//"Message.HealthPotion".MatchesTag("Message") will return true, "Message".MatchsTag("Message.HealthPotion") will return false
				if (Tag.MatchesTag(MessageTag))
				{
					FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					if (Row)
					{
						MessageWidgetRowDelegate.Broadcast(*Row);
					}
				}
			}
		}
	);
}

void UDestinyOverlayWidgetController::HealthChagned(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UDestinyOverlayWidgetController::MaxHealthChagned(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);

}
