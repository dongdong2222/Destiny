// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DestinyInventoryManagerComponent.generated.h"

class UDestinyInventoryItemInstance;



USTRUCT(BlueprintType)
struct FDestinyInventoryEntry
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<UDestinyInventoryItemInstance> Instance = nullptr;

};


//InventoryItem 관리 객체
USTRUCT(BlueprintType)
struct FDestinyInventoryList
{
	GENERATED_BODY()

	FDestinyInventoryList(UActorComponent* InOwnerComponent = nullptr)
		: OwnerComponent(InOwnerComponent)
	{
	}

	UPROPERTY()
	TArray<FDestinyInventoryEntry> Entrys;

	UPROPERTY()
	TObjectPtr<UActorComponent> OwnerComponent;
};


//PlayerController에 부착되어 Inventory를 관리하는 컴포넌트
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DESTINY_API UDestinyInventoryManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDestinyInventoryManagerComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY()
	FDestinyInventoryList InventoryList;
		
};
