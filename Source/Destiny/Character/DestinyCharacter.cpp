// Fill out your copyright notice in the Description page of Project Settings.


#include "DestinyCharacter.h"
#include "Destiny/AbilitySystem/DestinyAbilitySystemComponent.h"
#include "Destiny/Player/DestinyPlayerState.h"
#include "Destiny/Player/DestinyPlayerController.h"
#include "Destiny/UI/DestinyHUD.h"

// Sets default values
ADestinyCharacter::ADestinyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADestinyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADestinyCharacter::InitAbilityActorInfo()
{
	ADestinyPlayerState* DestinyPlayerState = GetPlayerState<ADestinyPlayerState>();
	check(DestinyPlayerState);
	DestinyPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(DestinyPlayerState, this);
	AbilitySystemComponent = DestinyPlayerState->GetAbilitySystemComponent();
	AbilitySet = DestinyPlayerState->GetAbilitySet();

	//멀티플레이 환경을 고려: 클라이언트의 경우 자신만의 PlayerController를 가지고 있기 때문에 다른 Player의 경우 null이 된다.
	//따라서 if check로 현재 플레이어만 실행하고 싶은 로직을 작성한다.
	//check()로 할 경우 멀티플레이 환경에서 동작하지 않는다. -> crash나니까
	if (ADestinyPlayerController* DestinyPlayerController = Cast<ADestinyPlayerController>(GetController()))
	{
		//HUD도 local 플레이어에게만 유효
		if (ADestinyHUD* DestinyHUD = Cast<ADestinyHUD>(DestinyPlayerController->GetHUD()))
		{
			DestinyHUD->InitOverlay(DestinyPlayerController, DestinyPlayerState, AbilitySystemComponent, AbilitySet);
		}

	}
}

void ADestinyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	//init ability actor info for the Server
	InitAbilityActorInfo();
}

void ADestinyCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	//init ability actor info for the client
	InitAbilityActorInfo();

}


UAbilitySystemComponent* ADestinyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called to bind functionality to input
void ADestinyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

