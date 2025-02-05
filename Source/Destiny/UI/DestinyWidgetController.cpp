// Fill out your copyright notice in the Description page of Project Settings.


#include "DestinyWidgetController.h"

void UDestinyWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParms)
{
	PlayerController = WCParms.PlayerController;
	PlayerState = WCParms.PlayerState;
	AbilitySystemComponent = WCParms.AbilitySystemComponent;
	AttributeSet = WCParms.AttributeSet;
}
