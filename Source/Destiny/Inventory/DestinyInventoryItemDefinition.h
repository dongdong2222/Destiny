// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DestinyInventoryItemDefinition.generated.h"



//아이템에 부착할 수 있는 컴포넌트 ->ItemDefinition에 부착가능
UCLASS(Abstract, DefaultToInstanced, EditInlineNew)
class UDestinyInventoryItemFragment : public UObject
{
	GENERATED_BODY()
public:

};




/**
 * InventoryItem의 메타데이터
 */
UCLASS()
class DESTINY_API UDestinyInventoryItemDefinition : public UObject
{
	GENERATED_BODY()
public:
	UDestinyInventoryItemDefinition(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//InventortItem 정의
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Display)
	FText DisplayName;

	//InventoryItem의 component를 fragment로
	//Instanced: 에디터를 통해서 부착하지만 CDO에도 반영되도록
	UPROPERTY(EditDefaultsOnly, Instanced, BlueprintReadOnly, Category = Display)
	TArray<TObjectPtr<UDestinyInventoryItemFragment>> Fragments;
	
};
