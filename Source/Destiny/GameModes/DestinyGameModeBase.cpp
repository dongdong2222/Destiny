// Fill out your copyright notice in the Description page of Project Settings.


#include "DestinyGameModeBase.h"
#include "DestinyExperienceDefinition.h"
#include "Kismet/GameplayStatics.h"
#include "Destiny/System/DestinyAssetManager.h"
#include "Destiny/DestinyLogChannels.h"

void ADestinyGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ThisClass::HandleMatchAssignmentIfNotExpectingOne);
}

void ADestinyGameModeBase::HandleMatchAssignmentIfNotExpectingOne()
{
	//이 함수의 목적은 ExperienceId와 ExperienceIdSource를 설정하는 것이다.
	FPrimaryAssetId ExperienceId;
	FString ExperienceIdSource;

	UWorld* World = GetWorld();

	if (!ExperienceId.IsValid() && UGameplayStatics::HasOption(OptionsString, TEXT("Experience")))
	{
		const FString ExperienceFromOptions = UGameplayStatics::ParseOption(OptionsString, TEXT("Experience"));
		ExperienceId = FPrimaryAssetId(FPrimaryAssetType(UDestinyExperienceDefinition::StaticClass()->GetFName()), FName(*ExperienceFromOptions));
		ExperienceIdSource = TEXT("OptionsString");
	}

	UDestinyAssetManager& AssetManager = UDestinyAssetManager::Get();
	FAssetData Dummy;
	if (ExperienceId.IsValid() && !AssetManager.GetPrimaryAssetData(ExperienceId, /*out*/ Dummy))
	{
		UE_LOG(LogDestinyExperience, Error, TEXT("EXPERIENCE: Wanted to use %s but couldn't find it, falling back to the default)"), *ExperienceId.ToString());
		ExperienceId = FPrimaryAssetId();
	}

	if (!ExperienceId.IsValid())
	{
		//if (TryDedicatedServerLogin())
		//{
		//	// This will start to host as a dedicated server
		//	return;
		//}

		ExperienceId = FPrimaryAssetId(FPrimaryAssetType("DestinyExperienceDefinition"), FName(TEXT("B_DestinyDefaultExperience")));
		ExperienceIdSource = TEXT("Default");
	}

	OnMatchAssignmentGiven(ExperienceId, ExperienceIdSource);
}

void ADestinyGameModeBase::OnMatchAssignmentGiven(FPrimaryAssetId ExperienceId, const FString& ExperienceIdSource)
{
	//
	if (ExperienceId.IsValid())
	{
		UE_LOG(LogDestinyExperience, Warning, TEXT("Identified experience %s (Source: %s)"), *ExperienceId.ToString(), *ExperienceIdSource);
		//UDestinyExperienceComponent* ExperienceComponent = GameState->FindComponentByClass<UDestinyExperienceComponent>();
		//ExperienceComponent->SetCurrentExperience(ExperienceId);
	}
	else
	{
		UE_LOG(LogDestinyExperience, Error, TEXT("Failed to identify experience, loading screen will stay up forever"));

	}
}
