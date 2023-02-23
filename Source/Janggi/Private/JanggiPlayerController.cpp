// Fill out your copyright notice in the Description page of Project Settings.


#include "JanggiPlayerController.h"
#include "SoundManager.h"
#include "JanggiGameModeBase.h"
#include "JanggiGameStateBase.h"
#include "Board.h"

#include "PowerAndHealthWidget.h"
#include "TimerUserWidget.h"
#include "LoseUserWidget.h"
#include "WinUserWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

AJanggiPlayerController::AJanggiPlayerController()
{
	bReplicates = true;
}

void AJanggiPlayerController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;
	bEnableMouseOverEvents = true;
	bEnableClickEvents = true;
	SetInputMode(FInputModeUIOnly());
}

void AJanggiPlayerController::ChangeWidget_Implementation(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (callCount==0)
	{
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASoundManager::StaticClass(), OutActors);
		for (AActor* a : OutActors)
		{
			SoundManager = Cast<ASoundManager>(a);
		}

		callCount++;
	}

	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}

	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

void AJanggiPlayerController::GameOver_Implementation(bool timeOut, int32 winner)
{
	const int Red = 1;
	const int Blue = 2;
	Cast<UTimerUserWidget>(CurrentWidget)->EndTimer();

	if (LoseClass != nullptr && WinClass != nullptr) // 위젯이 널이 아닐 때
	{
		LoserWidget = CreateWidget(GetWorld(), LoseClass);
		WinnerWidget = CreateWidget(GetWorld(), WinClass);
		if (LoserWidget != nullptr && WinnerWidget != nullptr)
		{
			if (timeOut) // 시간이 다 되어서 게임이 끝났을 때
			{
				Cast<ULoseUserWidget>(LoserWidget)->TimeOut();
				Cast<UWinUserWidget>(WinnerWidget)->TimeOut();
			}

			if (winner == Red) // 승자가 한나라
			{
				if (GetWorld()->GetFirstPlayerController()->GetLocalRole() == ROLE_Authority) // 서버 이김
				{
					WinnerWidget->AddToViewport();
					Cast<UWinUserWidget>(WinnerWidget)->WinAim();

					SoundManager->StopSound(JanggiMapBGM);
					SoundManager->PlaySound(WinSoundEffect, 3.0f);
					SoundManager->PlaySound(WinBGM, 1.0f);
				}
				else // 클라 짐
				{
					LoserWidget->AddToViewport();
					Cast<ULoseUserWidget>(LoserWidget)->LoseAim();

					SoundManager->StopSound(JanggiMapBGM);
					SoundManager->PlaySound(LoseSoundEffect, 3.0f);
					SoundManager->PlaySound(LoseBGM, 1.0f);
				}
			}
			else if (winner == Blue) // 승자가 초나라
			{
				if (GetWorld()->GetFirstPlayerController()->GetLocalRole() == ROLE_Authority) // 서버 짐
				{
					LoserWidget->AddToViewport();
					Cast<ULoseUserWidget>(LoserWidget)->LoseAim();

					SoundManager->StopSound(JanggiMapBGM);
					SoundManager->PlaySound(LoseSoundEffect, 3.0f);
					SoundManager->PlaySound(LoseBGM, 1.0f);
				}
				else  // 클라 이김
				{
					WinnerWidget->AddToViewport();
					Cast<UWinUserWidget>(WinnerWidget)->WinAim();

					SoundManager->StopSound(JanggiMapBGM);
					SoundManager->PlaySound(WinSoundEffect, 3.0f);
					SoundManager->PlaySound(WinBGM, 1.0f);
				}
			}
		}
	}

	SetInputMode(FInputModeUIOnly());
}

void AJanggiPlayerController::GameStart_Implementation()
{
	PlayBGM(SelectBGM, JanggiMapBGM, JanggiMapBGMVol); // 게임 시작할때 브금 바꿈
	if (ShowPowerHealthWidget != nullptr)
	{
		ShowPowerHealthWidget->RemoveFromViewport();
		ShowPowerHealthWidget = nullptr;
	}

	if (ShowPowerHealthClass != nullptr)
	{
		ShowPowerHealthWidget = CreateWidget(GetWorld(), ShowPowerHealthClass);
		if (ShowPowerHealthWidget != nullptr)
		{
			ShowPowerHealthWidget->AddToViewport();
		}
	}

	SetInputMode(FInputModeGameOnly());
	JanggiBoard->BP_StartEvent();
	JanggiBoard->SetMouseOver();
	Cast<UTimerUserWidget>(CurrentWidget)->StartTimer();
}

void AJanggiPlayerController::PlayBGM_Implementation(int32 StopBGM, int32 PlayBGM, float volume)
{
	SoundManager->StopSound(StopBGM);
	SoundManager->LoopingSound(PlayBGM);
	SoundManager->PlaySound(PlayBGM, volume);
}

void AJanggiPlayerController::ShowPowerHealth(int32 pieciesIndex, int32 power, int32 health)
{
	Cast<UPowerAndHealthWidget>(ShowPowerHealthWidget)->ShowPowerHealth(pieciesIndex, power, health);
}

void AJanggiPlayerController::SetServerIsReady()
{
	Cast<AJanggiGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->SetReadyServer();
}

void AJanggiPlayerController::ResetMyturn()
{
	Cast<UTimerUserWidget>(CurrentWidget)->ResetMyturn();
}

void AJanggiPlayerController::SetClientIsReady_Implementation()
{
	Cast<AJanggiGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->SetbReadyClient();
}

void AJanggiPlayerController::SetGameTurn_Implementation()
{
	const int Red = 1;
	const int Blue = 2;
	if (JanggiState->GetGameTurn() == Blue) JanggiState->SetGameTurn(Red); // 이동후 현재 게임턴을 바꿔 준다.
	else JanggiState->SetGameTurn(Blue);
}

void AJanggiPlayerController::SetLastTurn_Implementation()
{
	JanggiState->SetlastTurn(JanggiState->GetGameTurn()); // 이동 전 게임턴을 저장해 놓는다.
}

void AJanggiPlayerController::CountTurn(bool gameTurn)
{
	Cast<UTimerUserWidget>(CurrentWidget)->CountTurn(gameTurn);

}

void AJanggiPlayerController::SetATK_Implementation(int32 curPosition, int32 lastClick)
{
	bIsDestroy = JanggiState->AttackPiecies(curPosition, lastClick);
}

void AJanggiPlayerController::SelectPosition_Implementation(int32 pos, int32 pieces)
{
	for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; Iter++)
	{
		Cast<AJanggiPlayerController>(Iter->Get())->SelectClientPosition(pos, pieces); // 서버에서 컨트롤러를 찾은 뒤 클라이언트의 기물을 변경한다.
	}
}

void AJanggiPlayerController::SelectClientPosition_Implementation(int32 pos, int32 pieces)
{
	JanggiState->WidgetSelectPosition(pos, pieces); // 말 위치 변경
}

void AJanggiPlayerController::ReStartReadyClient_Implementation(bool ready)
{
	Cast<AJanggiGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->ReStartbReadyClient(ready);
}

void AJanggiPlayerController::ReStartReadyServer()
{
	Cast<AJanggiGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->ReStartReadyServer();
}

void AJanggiPlayerController::ServerMeue_Implementation()
{
	UGameplayStatics::OpenLevel(this, FName(TEXT("Server")));
}

void AJanggiPlayerController::RemoveResultWidget()
{
	if (LoserWidget != nullptr)
	{
		LoserWidget->RemoveFromViewport();
		LoserWidget = nullptr;
	}
	if (WinnerWidget != nullptr)
	{
		WinnerWidget->RemoveFromViewport();
		WinnerWidget = nullptr;
	}
}

void AJanggiPlayerController::SetSkillUsing_Implementation(bool IsSkill)
{
	JanggiState->SetSkillUsing(IsSkill);
}

void AJanggiPlayerController::ResetBoard()
{
	JanggiBoard->ReStart();
}

void AJanggiPlayerController::UsingSkill(int32 skillCount)
{
	Cast<UTimerUserWidget>(CurrentWidget)->SetSkillCount(skillCount);
}