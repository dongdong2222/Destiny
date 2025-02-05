// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DestinyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class DESTINY_API UDestinyUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;
protected:
	//WidgerController가 설정됐을 때 로직 blueprint에서 작성하도록
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
