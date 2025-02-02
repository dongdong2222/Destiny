// Fill out your copyright notice in the Description page of Project Settings.


#include "DestinyUserFacingExperience.h"
#include "CommonSessionSubsystem.h"
#include "Destiny/DestinyLogChannels.h"

UCommonSession_HostSessionRequest* UDestinyUserFacingExperience::CreateHostingRequest(const UObject* WorldContextObject) const
{
   //이 함수의 목적은 PrimaryAsset의 데이터에 맞춰 UCommonSession_HostSessionRequest를 생성하는 것
   
   const FString ExperienceName = ExperienceID.PrimaryAssetName.ToString();
   const FString UserFacingExperienceName = GetPrimaryAssetId().PrimaryAssetName.ToString();

   UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);
   UGameInstance* GameInstance = World ? World->GetGameInstance() : nullptr;
   UCommonSession_HostSessionRequest* Result = nullptr;

   if (UCommonSessionSubsystem* Subsystem = GameInstance ? GameInstance->GetSubsystem<UCommonSessionSubsystem>() : nullptr)
   {
      Result = Subsystem->CreateOnlineHostSessionRequest();
   }

   if (!Result)
   {
      UE_LOG(LogDestinyExperience, Warning, TEXT("CreateOnlineHostSessionRequest is failed"));
      // Couldn't use the subsystem so create one
      Result = NewObject<UCommonSession_HostSessionRequest>();
      Result->OnlineMode = ECommonSessionOnlineMode::Online;
      Result->bUseLobbies = true;
      Result->bUseLobbiesVoiceChat = false;
      // We always enable presence on this session because it is the primary session used for matchmaking. For online systems that care about presence, only the primary session should have presence enabled
      Result->bUsePresence = !IsRunningDedicatedServer();
   }
   Result->MapID = MapID;
   Result->ModeNameForAdvertisement = UserFacingExperienceName;
   //Result->ExtraArgs = ExtraArgs;
   Result->ExtraArgs.Add(TEXT("Experience"), ExperienceName);
   //Result->MaxPlayerCount = MaxPlayerCount;

   //if (ULyraReplaySubsystem::DoesPlatformSupportReplays())
   //{
   //   if (bRecordReplay)
   //   {
   //      Result->ExtraArgs.Add(TEXT("DemoRec"), FString());
   //   }
   //}

    return Result;
}
