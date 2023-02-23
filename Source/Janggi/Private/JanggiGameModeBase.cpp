// Copyright Epic Games, Inc. All Rights Reserved.


#include "JanggiGameModeBase.h"
#include "SoundManager.h"
#include "JanggiPlayerController.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"

void AJanggiGameModeBase::BeginPlay()
{
	Super::BeginPlay();

}

void AJanggiGameModeBase::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);

}

void AJanggiGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	AJanggiPlayerController* Controller = Cast<AJanggiPlayerController>(NewPlayer);

	if (Controller)
	{
		Controller->ChangeWidget(WaitingWidgetClass);
		Controller->PlayBGM(WaitingBGM, WaitingBGM, 2.0f);
	}
	if (GetWorld()->GetNumPlayerControllers() == 2)
	{
		for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; Iter++)
		{
			Cast<AJanggiPlayerController>(Iter->Get())->ChangeWidget(MainWidgetClass);
			Cast<AJanggiPlayerController>(Iter->Get())->PlayBGM(WaitingBGM, SelectBGM, 1.0f);
		}
	}
}

void AJanggiGameModeBase::SetbReadyClient()
{
	bReadyClient = true;
	GameStart();
}

void AJanggiGameModeBase::SetReadyServer()
{
	bReadyServer = true;
	GameStart();
}

void AJanggiGameModeBase::ReStartReadyServer()
{
	bReadyServer = true;
	ReStart();
}

void AJanggiGameModeBase::ReStartbReadyClient(bool ready)
{

	if (ready)
	{
		bReadyClient = true;
		ReStart();
	}
	else
	{
		for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; Iter++)
		{
			Cast<AJanggiPlayerController>(Iter->Get())->ServerMeue();
		}
	}
}

void AJanggiGameModeBase::GameStart()
{
	if (bReadyClient && bReadyServer)
	{
		for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; Iter++)
		{
			Cast<AJanggiPlayerController>(Iter->Get())->ChangeWidget(TimerWidgetClass);
			Cast<AJanggiPlayerController>(Iter->Get())->GameStart();
		}
		Cast<AJanggiPlayerController>(GetWorld()->GetFirstPlayerController())->ResetMyturn();
		bReadyClient = false;
		bReadyServer = false;
	}
}

void AJanggiGameModeBase::ReStart()
{
	if (bReadyClient && bReadyServer)
	{
		for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; Iter++)
		{
			Cast<AJanggiPlayerController>(Iter->Get())->ChangeWidget(MainWidgetClass);
			Cast<AJanggiPlayerController>(Iter->Get())->PlayBGM(WaitingBGM, SelectBGM, 1.0f);
		}
		bReadyClient = false;
		bReadyServer = false;
	}
}