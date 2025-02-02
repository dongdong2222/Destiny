// Fill out your copyright notice in the Description page of Project Settings.


#include "DestinyAssetManager.h"
#include "Destiny/DestinyLogChannels.h"


UDestinyAssetManager::UDestinyAssetManager()
{
}

UDestinyAssetManager& UDestinyAssetManager::Get()
{
	check(GEngine);
	//GEngine::TObjectPtr<class UAssetManager> AssetManager에 캐싱되어있다
	if (UDestinyAssetManager* Singleton = Cast<UDestinyAssetManager>(GEngine->AssetManager))
	{
		return *Singleton;
	}
	UE_LOG(D_Log, Fatal, TEXT("invalid AssetManangerClass"));

	return *NewObject<UDestinyAssetManager>();
}

bool UDestinyAssetManager::ShouldLogAssetLoads()
{
	const TCHAR* CommandLindContent = FCommandLine::Get();
	static bool bLogAssetLoads = FParse::Param(CommandLindContent, TEXT("LogAssetLoads"));
	return bLogAssetLoads;
}


UObject* UDestinyAssetManager::SynchronousLoadAsset(const FSoftObjectPath& AssetPath)
{
	//해당 함수를 따로 만든 이유는 'synchronous(동기식) load asset이 불필요하게 하는 것이 없는지 확인하기 위함
	if (AssetPath.IsValid())
	{
		//FScopeLogTime을 확인 -> 로드시 얼마나 걸렸나
		TUniquePtr<FScopeLogTime> LogTimePtr;
		if (ShouldLogAssetLoads())
		{
			//로깅하면서, 초단위로 로깅
			LogTimePtr = MakeUnique<FScopeLogTime>(*FString::Printf(TEXT("synchronous loaded assets [%s]"), *AssetPath.ToString()), nullptr, FScopeLogTime::ScopeLog_Seconds);
		}
		//동기적 로딩 : 로딩 시 게임 일시정지, 정적 로딩: 게임 시작 전 에셋이 로드된 상태로 존재

		//2가지 분기
		//1. assetManager가 있으면, AssetManager의 StreamableManager를 통해 정적 로딩
		//2. 아니면, FSoftObjectPath를 통해 바로 정적 로딩
		if (UAssetManager::IsInitialized())
		{
			return UAssetManager::GetStreamableManager().LoadSynchronous(AssetPath);
		}

		// if asset manager is not ready, use LoadObject()
		// - 슥 보고 StaticLoadObject가 보인다 -> 캐시 되어있다.
		// - 참고로, 항상 StaticLoaadObject를 하기 전에 StaticFindObject를 통해 확인하고 실패시 진짜 로딩함
		return AssetPath.TryLoad();

	}
	return nullptr;
}

void UDestinyAssetManager::AddLoadedAsset(const UObject* Asset)
{
	if (ensureAlways(Asset))
	{
		FScopeLock LoadedAssetsLock(&LoadedAssetsCritical);
		LoadedAssets.Add(Asset);
	}
}
