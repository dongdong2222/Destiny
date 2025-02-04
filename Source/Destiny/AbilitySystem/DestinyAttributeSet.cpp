// Fill out your copyright notice in the Description page of Project Settings.


#include "DestinyAttributeSet.h"
#include "Net/UnrealNetwork.h"

UDestinyAttributeSet::UDestinyAttributeSet()
{
	InitHealth(100.f);
	InitMaxHealth(100.f);
	InitMana(10.f);
	InitMaxMana(20.f);
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
