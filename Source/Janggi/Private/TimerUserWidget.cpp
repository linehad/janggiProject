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
	// Ÿ�̸� �ڵ鷯�� ���� �ð��� ������Ʈ�Ѵ�.
	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &UTimerUserWidget::CountDown, 1.f, true, 0.0);
	JanggiState = Cast<AJanggiGameStateBase>(GetWorld()->GetGameState());
}
void UTimerUserWidget::EndTimer()
{
	// Ÿ�̸� �ڵ鷯�� ���� �ð��� ������Ʈ�Ѵ�.
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

	if (GetWorld()->GetFirstPlayerController()->GetLocalRole() == ROLE_Authority) // ���� ����
	{
		if (enemyMinute == 0 && enemySeconds == 0) // ����� �ð��� ���� ��
		{
			for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; Iter++)
			{
				Cast<AJanggiPlayerController>(Iter->Get())->GameOver(true, Red);
			}
		}
		else if (myMinute == 0 && mySeconds == 0) // �� �ð��� ���� ��
		{
			for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; Iter++)
			{
				Cast<AJanggiPlayerController>(Iter->Get())->GameOver(true, Blue);
			}
		}
		else if (JanggiState->GetGameTurn() == Red) // �� ���� ���� ��
		{
			CountMyTime();
		}
		else // ��� ���� ��
		{
			CountEnemyTime();
		}
	}
	
	else // Ŭ���� ��
	{
		if (JanggiState->GetGameTurn() == Blue) // �� ���� ���� ��
		{
			CountMyTime();
		}
		else // ��� ���� ��
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
	if (mySeconds != 0) // �� �ʰ� 0�� �ƴ϶��
	{
		mySeconds--;
	}
	else // 0�� �Ǹ� ���� �ʷ� �ٲ�
	{
		myMinute--;
		mySeconds = 59;
		MyMinuteTextBlock->SetText(FText::FromString(FString::FromInt(myMinute)));
	}
	MySecondsTextBlock->SetText(FText::FromString(FString::FromInt(mySeconds)));
}

void UTimerUserWidget::CountEnemyTime()
{
	if (enemySeconds != 0) // �� �ʰ� 0�� �ƴ϶��
	{
		enemySeconds--;
	}
	else // 0�� �Ǹ� ���� �ʷ� �ٲ�
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
	
	// ���� ���� �� Ŭ�� ������ �ƹ��͵� ����
	if (RED_TURN == JanggiState->GetGameTurn() && GetWorld()->GetFirstPlayerController()->GetRemoteRole() == ROLE_Authority)
	{
		SoundManager->PlaySound(NoSkillSoundEffect, 0.5f);
		return;
	}
	// Ŭ�� ���� �� ������ ������ �ƹ��͵� ����
	else if(BLUE_TURN == JanggiState->GetGameTurn() && GetWorld()->GetFirstPlayerController()->GetLocalRole() == ROLE_Authority)
	{
		SoundManager->PlaySound(NoSkillSoundEffect, 0.5f);
		return;
	}
	Cast<AJanggiPlayerController>(GetWorld()->GetFirstPlayerController())->SetSkillUsing(true);
	SoundManager->PlaySound(ButtonClickSoundEffect, 3.0f);
}