// Fill out your copyright notice in the Description page of Project Settings.


#include "DestinyHUD.h"
#include "Destiny/UI/DestinyUserWidget.h"
#include "Destiny/UI/DestinyOverlayWidgetController.h"

UDestinyOverlayWidgetController* ADestinyHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (!OverlayWidgetController)
	{
		OverlayWidgetController = NewObject<UDestinyOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbackToDependencies();

	}
	return OverlayWidgetController;
}


void ADestinyHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass uninitialized, please fill out BP_DestinyHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetClass uninitialized, please fill out BP_DestinyHUD"));

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UDestinyUserWidget>(Widget);

	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UDestinyOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	
	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();

	OverlayWidget->AddToViewport();
}

