// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DestinyWidgetController.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;


USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()
	FWidgetControllerParams() {};
	FWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
		:PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS)
	{ }

	//Widget들에게 broadcast하고 싶은 데이터를 받을 객체들
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;

};

/**
 * 
 */
UCLASS()
class DESTINY_API UDestinyWidgetController : public UObject
{
	GENERATED_BODY()
public:
	void SetWidgetControllerParams(const FWidgetControllerParams& WCParms);
protected:
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;

	
};
