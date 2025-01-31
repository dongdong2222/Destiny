// Copyright Epic Games, Inc. All Rights Reserved.

#include "Destiny.h"
#include "Modules/ModuleManager.h"

class FDestinyGameModule : public FDefaultGameModuleImpl
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

void FDestinyGameModule::StartupModule()
{
	FDefaultGameModuleImpl::StartupModule();
	UE_LOG(LogTemp, Log, TEXT("StartupModule"));
}

void FDestinyGameModule::ShutdownModule()
{
	FDefaultGameModuleImpl::ShutdownModule();
	UE_LOG(LogTemp, Log, TEXT("ShutdownModule"));

}

//PRIMARY MODULE은 하나만 Implement 가능
//추가적인 모듈은 IMPLEMENT_GAME_MODULE
IMPLEMENT_PRIMARY_GAME_MODULE(FDestinyGameModule, Destiny, "Destiny" );