// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "DestinyAssetManager.generated.h"

/**
 * PrimaryAsset?? : 
 */
UCLASS()
class DESTINY_API UDestinyAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	UDestinyAssetManager();

	static UDestinyAssetManager& Get();

	static bool ShouldLogAssetLoads();

	UObject* SynchronousLoadAsset(const FSoftObjectPath& AssetPath);
	
	template <class AssetType>
	static AssetType* GetAsset(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemory = true);

	template <class AssetType>
	static TSubclassOf<AssetType> GetSubclass(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemory = true);

	void AddLoadedAsset(const UObject* Asset);

	//GC의 대상
	UPROPERTY()
	TSet<TObjectPtr<const UObject>> LoadedAssets;

	//Object 단위 locking
	FCriticalSection LoadedAssetsCritical;
};

template<class AssetType>
inline AssetType* UDestinyAssetManager::GetAsset(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemory)
{
	AssetType* LoadedAsset = nullptr;

	const FSoftObjectPath& AssetPath = AssetPointer.ToSoftObjectPath();


	if (AssetPath.IsValid())
	{
		//Get() -> 로드되어 있다면 바로 가져옴
		//      -> 로드되어 있지 않다면 Null
		LoadedAsset = AssetPointer.Get();
		if (!LoadedAsset)
		{
			LoadedAsset = Cast<AssetType>(SynchronousLoadAsset(AssetPath));
			ensureAlwaysMsgf(LoadedAsset, TEXT("Failed to load asset [%s]"), *AssetPointer.ToString());
		}

		if (LoadedAsset && bKeepInMemory)
		{
			// Added to loaded asset list.
			Get().AddLoadedAsset(Cast<UObject>(LoadedAsset));
		}
	}

	return LoadedAsset;
}

template<class AssetType>
inline TSubclassOf<AssetType> UDestinyAssetManager::GetSubclass(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemory)
{
	TSubclassOf<AssetType> LoadedSubclass;

	const FSoftObjectPath& AssetPath = AssetPointer.ToSoftObjectPath();

	if (AssetPath.IsValid())
	{
		LoadedSubclass = AssetPointer.Get();
		if (!LoadedSubclass)
		{
			LoadedSubclass = Cast<UClass>(SynchronousLoadAsset(AssetPath));
			ensureAlwaysMsgf(LoadedSubclass, TEXT("Failed to load asset class [%s]"), *AssetPointer.ToString());
		}

		if (LoadedSubclass && bKeepInMemory)
		{
			// Added to loaded asset list.
			// AddLoadedAsst은 메모리에 상주하기 위한 장치
			// 한 번 등록되면 직접 내리지 않는 한 Unload되지 않음( ** 캐싱), GC가 회수하지 않도록
			Get().AddLoadedAsset(Cast<UObject>(LoadedSubclass));
		}
	}

	return LoadedSubclass;
}

