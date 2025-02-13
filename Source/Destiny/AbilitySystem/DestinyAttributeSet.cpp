// Fill out your copyright notice in the Description page of Project Settings.


#include "DestinyAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "AbilitySystemBlueprintLibrary.h"


UDestinyAttributeSet::UDestinyAttributeSet()
{
	InitHealth(100.f);
	InitMaxHealth(200.f);
	InitMana(50.f);
	InitMaxMana(100.f);
}

void UDestinyAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//값이 바뀌지 않아도 Replicate 되도록??
	DOREPLIFETIME_CONDITION_NOTIFY(UDestinyAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDestinyAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDestinyAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDestinyAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UDestinyAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}

void UDestinyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	FEffectProperties EffectProperties;
	SetEffectProperties(Data, EffectProperties);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3.f)
	}
}

void UDestinyAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	//health 속성이 변경되었을때 클라이언트가 이를 감지할 수 있게 해줌(Broadcast해줌으로써
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDestinyAttributeSet, Health, OldHealth);

}

void UDestinyAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	//health 속성이 변경되었을때 클라이언트가 이를 감지할 수 있게 해줌(Broadcast해줌으로써
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDestinyAttributeSet, MaxHealth, OldMaxHealth);
}

void UDestinyAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	//health 속성이 변경되었을때 클라이언트가 이를 감지할 수 있게 해줌(Broadcast해줌으로써
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDestinyAttributeSet, Mana, OldMana);
}

void UDestinyAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	//health 속성이 변경되었을때 클라이언트가 이를 감지할 수 있게 해줌(Broadcast해줌으로써
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDestinyAttributeSet, MaxMana, OldMaxMana);
}

void UDestinyAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	//Source = courser of the effect, Target = Target of the effect
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	//Source
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->GetAvatarActor();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (Props.SourceController == nullptr && Props.SourceAvatarActor == nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}
	//Target
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.SourceAvatarActor);

	}

}
