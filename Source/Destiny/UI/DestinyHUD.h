// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DestinyHUD.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

class UDestinyUserWidget;
class UDestinyOverlayWidgetController;
struct FWidgetControllerParams;

/**
 * 
 */
UCLASS()
class DESTINY_API ADestinyHUD : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TObjectPtr<UDestinyUserWidget> OverlayWidget;

	UDestinyOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);


private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UDestinyUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UDestinyOverlayWidgetController> OverlayWidgetController;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UDestinyOverlayWidgetController> OverlayWidgetControllerClass;

};
