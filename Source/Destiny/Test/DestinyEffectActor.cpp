// Fill out your copyright notice in the Description page of Project Settings.


#include "DestinyEffectActor.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "Destiny/AbilitySystem/DestinyAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"

// Sets default values
ADestinyEffectActor::ADestinyEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(RootComponent);


}

void ADestinyEffectActor::ApplyEffecttoTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!TargetASC) return;

	check(GameplayEffectClass);
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContextHandle);
	FGameplayEffectSpec spec;
	
	FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	if (EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite)
	{
		ActiveGameplayEffects.Add(ActiveEffectHandle, TargetASC);
	}
}

void ADestinyEffectActor::OnOverlap(AActor* TargetActor)
{
	if (InstantGameplayAppicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffecttoTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationGameplayAppicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffecttoTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteGameplayAppicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffecttoTarget(TargetActor, InfiniteGameplayEffectClass);
	}
}

void ADestinyEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantGameplayAppicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffecttoTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationGameplayAppicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffecttoTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteGameplayAppicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffecttoTarget(TargetActor, InfiniteGameplayEffectClass);
	}



	if (InfiniteGameplayRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!TargetASC) return;

		TArray<FActiveGameplayEffectHandle> HandleToRemove;
		for (auto& ActiveEffect : ActiveGameplayEffects)
		{
			if (TargetASC == ActiveEffect.Value)
			{
				TargetASC->RemoveActiveGameplayEffect(ActiveEffect.Key);
				HandleToRemove.Add(ActiveEffect.Key);
			}
		}
		for (auto& EffectHandle : HandleToRemove)
		{
			ActiveGameplayEffects.FindAndRemoveChecked(EffectHandle);
		}
	}
}





