// Fill out your copyright notice in the Description page of Project Settings.


#include "DestinyPlayerController.h"

ADestinyPlayerController::ADestinyPlayerController()
{
}

void ADestinyPlayerController::AcknowledgePossession(APawn* pawn)
{
	//이 함수는 새로운 pawn을 possess했을때 확인하는 용도로 실행되는 함수
	Super::AcknowledgePossession(pawn);
	//클라이언트 초기화
	//
}


