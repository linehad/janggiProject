// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerUserWidget.h"
#include "SoundManager.h"
#include "JanggiPlayerController.h"
#include <Components/Button.h>
#include "JanggiGameStateBase.h"

#include "Kismet/GameplayStatics.h"
#include "Animation/WidgetAnimation.h"
#include "Components/TextBlock.h"

void UTimerUserWidget::NativeConstruct()
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASoundManager::StaticClass(), OutActors);
	for (AActor* a : OutActors)
	{
		SoundManager = Cast<ASoundManager>(a);
	}
	SkillButton->OnClicked.AddDynamic(this, &UTimerUserWidget::SkillButtonCallback);
}

void UTimerUserWidget::StartTimer()
{
	// 타이머 핸들러를 통해 시간을 업데이트한다.
	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &UTimerUserWidget::CountDown, 1.f, true, 0.0);
	JanggiState = Cast<AJanggiGameStateBase>(GetWorld()->GetGameState());
}
void UTimerUserWidget::EndTimer()
{
	// 타이머 핸들러를 통해 시간을 업데이트한다.
	GetWorld()->GetTimerManager().ClearTimer(timerHandle);
}


void UTimerUserWidget::CountTurn(bool turn)
{
	if (turn)
	{
		myTurn++;
		PlayAnimation(TurnAim);
		TurnTextBlock->SetText(FText::FromString(FString::FromInt(myTurn)));
		SoundManager->PlaySound(TurnSoundEffect, 3.0f);
	}
}

void UTimerUserWidget::CountDown()
{
	const int Red = 1;
	const int Blue = 2;

	if (GetWorld()->GetFirstPlayerController()->GetLocalRole() == ROLE_Authority) // 서버 전용
	{
		if (enemyMinute == 0 && enemySeconds == 0) // 상대의 시간이 없을 때
		{
			for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; Iter++)
			{
				Cast<AJanggiPlayerController>(Iter->Get())->GameOver(true, Red);
			}
		}
		else if (myMinute == 0 && mySeconds == 0) // 내 시간이 없을 때
		{
			for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; Iter++)
			{
				Cast<AJanggiPlayerController>(Iter->Get())->GameOver(true, Blue);
			}
		}
		else if (JanggiState->GetGameTurn() == Red) // 한 나라 턴일 때
		{
			CountMyTime();
		}
		else // 상대 턴일 때
		{
			CountEnemyTime();
		}
	}
	
	else // 클라일 때
	{
		if (JanggiState->GetGameTurn() == Blue) // 초 나라 턴일 때
		{
			CountMyTime();
		}
		else // 상대 턴일 때
		{
			CountEnemyTime();
		}
	}
}

void UTimerUserWidget::ResetMyturn()
{
	TurnTextBlock->SetText(FText::FromString(FString::FromInt(myTurn)));
}

void UTimerUserWidget::SetSkillCount(int32 count)
{
	SkillTextBlock->SetText(FText::FromString(FString::FromInt(count)));
	if (count <= 0)
	{
		SkillButton->SetIsEnabled(false);
	}
}

void UTimerUserWidget::CountMyTime()
{
	if (mySeconds != 0) // 내 초가 0이 아니라면
	{
		mySeconds--;
	}
	else // 0이 되면 분을 초로 바꿈
	{
		myMinute--;
		mySeconds = 59;
		MyMinuteTextBlock->SetText(FText::FromString(FString::FromInt(myMinute)));
	}
	MySecondsTextBlock->SetText(FText::FromString(FString::FromInt(mySeconds)));
}

void UTimerUserWidget::CountEnemyTime()
{
	if (enemySeconds != 0) // 내 초가 0이 아니라면
	{
		enemySeconds--;
	}
	else // 0이 되면 분을 초로 바꿈
	{
		enemyMinute--;
		enemySeconds = 59;
		EnemyMinuteTextBlock->SetText(FText::FromString(FString::FromInt(enemyMinute)));
	}
	EnemySecondsTextBlock->SetText(FText::FromString(FString::FromInt(enemySeconds)));
}

void UTimerUserWidget::SkillButtonCallback()
{
	const int32	RED_TURN = 1;
	const int32	BLUE_TURN = 2;
	
	// 서버 턴일 때 클라가 누르면 아무것도 안함
	if (RED_TURN == JanggiState->GetGameTurn() && GetWorld()->GetFirstPlayerController()->GetRemoteRole() == ROLE_Authority)
	{
		SoundManager->PlaySound(NoSkillSoundEffect, 0.5f);
		return;
	}
	// 클라 턴일 때 서버가 누르면 아무것도 안함
	else if(BLUE_TURN == JanggiState->GetGameTurn() && GetWorld()->GetFirstPlayerController()->GetLocalRole() == ROLE_Authority)
	{
		SoundManager->PlaySound(NoSkillSoundEffect, 0.5f);
		return;
	}
	Cast<AJanggiPlayerController>(GetWorld()->GetFirstPlayerController())->SetSkillUsing(true);
	SoundManager->PlaySound(ButtonClickSoundEffect, 3.0f);
}