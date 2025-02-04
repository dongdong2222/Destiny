// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DestinyInventoryItemInstance.generated.h"

class UDestinyInventoryItemDefinition;
/**
 * InventoryDefinition의 메타데이터를 이용해서 실제 인스턴스 생성
 */
UCLASS()
class DESTINY_API UDestinyInventoryItemInstance : public UObject
{
	GENERATED_BODY()
public:
	UDestinyInventoryItemInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	UPROPERTY()
	TSubclassOf<UDestinyInventoryItemDefinition> ItemDef;

};
