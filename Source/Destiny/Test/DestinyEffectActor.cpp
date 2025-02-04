// Fill out your copyright notice in the Description page of Project Settings.


#include "DestinyEffectActor.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "Destiny/AbilitySystem/DestinyAttributeSet.h"

// Sets default values
ADestinyEffectActor::ADestinyEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(RootComponent);

	//Sphere->OnComponentBeginOverlap.AddDynamic(this, &ADestinyEffectActor::OnOverlap);
	//Sphere->OnComponentEndOverlap.AddDynamic(this, &ADestinyEffectActor::OnEndOverlap);
}

void ADestinyEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO : Change this to apply a Gameplay Effect
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UDestinyAttributeSet* DestinyAttributeSet = Cast<UDestinyAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UDestinyAttributeSet::StaticClass()));
		UDestinyAttributeSet* DestinyAttributeSetNoConst = const_cast<UDestinyAttributeSet*>(DestinyAttributeSet);
		DestinyAttributeSetNoConst->SetHealth(DestinyAttributeSet->GetHealth() + 25.f);
	}
}

void ADestinyEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}



