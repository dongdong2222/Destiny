// Fill out your copyright notice in the Description page of Project Settings.


#include "DestinyUserWidget.h"

void UDestinyUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
