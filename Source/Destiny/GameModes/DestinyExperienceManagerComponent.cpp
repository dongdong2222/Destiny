// Fill out your copyright notice in the Description page of Project Settings.


#include "DestinyExperienceManagerComponent.h"
#include "Destiny/System/DestinyAssetManager.h"
#include "Destiny/GameModes/DestinyExperienceDefinition.h"
#include "Destiny/DestinyLogChannels.h"

UDestinyExperienceManagerComponent::UDestinyExperienceManagerComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UDestinyExperienceManagerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UDestinyExperienceManagerComponent::SetCurrentExperience(FPrimaryAssetId ExperienceId)
{
	UDestinyAssetManager& AssetManager = UDestinyAssetManager::Get();
	FSoftObjectPath AssetPath = AssetManager.GetPrimaryAssetPath(ExperienceId);
	TSubclassOf<UDestinyExperienceDefinition> AssetClass = Cast<UClass>(AssetPath.TryLoad());
	check(AssetClass);
	const UDestinyExperienceDefinition* Experience = GetDefault<UDestinyExperienceDefinition>(AssetClass);

	check(Experience != nullptr);
	check(CurrentExperience == nullptr);
	CurrentExperience = Experience;

}

void UDestinyExperienceManagerComponent::StartExperienceLoad()
{
	check(CurrentExperience != nullptr);
	check(LoadState == EDestinyExperienceLoadState::Unloaded);

	UE_LOG(LogDestinyExperience, Log, TEXT("EXPERIENCE: StartExperienceLoad(CurrentExperience = %s)"),
		*CurrentExperience->GetPrimaryAssetId().ToString());

	LoadState = EDestinyExperienceLoadState::Loading;

	UDestinyAssetManager& AssetManager = UDestinyAssetManager::Get();

	TSet<FPrimaryAssetId> BundleAssetList;
	TSet<FSoftObjectPath> RawAssetList;

	BundleAssetList.Add(CurrentExperience->GetPrimaryAssetId());
	//for (const TObjectPtr<ULyraExperienceActionSet>& ActionSet : CurrentExperience->ActionSets)
	//{
	//	if (ActionSet != nullptr)
	//	{
	//		BundleAssetList.Add(ActionSet->GetPrimaryAssetId());
	//	}
	//}

	TArray<FName> BundlesToLoad;
	//BundlesToLoad.Add(FDestinyBundles::Equipped);
}
