// Fill out your copyright notice in the Description page of Project Settings.


#include "WinUserWidget.h"
#include "SoundManager.h"
#include "JanggiPlayerController.h"

#include "Animation/WidgetAnimation.h"
#include "Components/TextBlock.h"
#include <Components/Button.h>

#include "Kismet/GameplayStatics.h"
void UWinUserWidget::NativeConstruct()
{
	EndButton->OnClicked.AddDynamic(this, &UWinUserWidget::EndButtonCallback);
	MainButton->OnClicked.AddDynamic(this, &UWinUserWidget::CallBack_MainButton);
	ReStartButton->OnClicked.AddDynamic(this, &UWinUserWidget::CallBack_ReStartButton);

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASoundManager::StaticClass(), OutActors);
	for (AActor* a : OutActors)
	{
		SoundManager = Cast<ASoundManager>(a);
	}
}

void UWinUserWidget::TimeOut() // 시간 승만 보이게 함
{
	WinTextBlock->SetVisibility(ESlateVisibility::Hidden);
	TimeWinTextBlock->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UWinUserWidget::EndButtonCallback()
{
	Cast<AJanggiPlayerController>(GetWorld()->GetFirstPlayerController())->ReStartReadyClient(false);
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}

void UWinUserWidget::CallBack_MainButton()
{
	Cast<AJanggiPlayerController>(GetWorld()->GetFirstPlayerController())->ReStartReadyClient(false);
}

void UWinUserWidget::CallBack_ReStartButton()
{

	SoundManager->StopSound(WinBGM);
	SoundManager->PlaySound(WaitingBGM, 2.0f);

	AJanggiPlayerController* Controller = Cast<AJanggiPlayerController>(GetWorld()->GetFirstPlayerController());
	Controller->ChangeWidget(WaitingWidgetClass);
	if (GetWorld()->GetFirstPlayerController()->GetLocalRole() == ROLE_Authority)
	{
		Controller->ReStartReadyServer();
	}
	else
	{
		Controller->ReStartReadyClient(true);
	}
	Controller->ResetBoard();
	Controller->RemoveResultWidget();
}

void UWinUserWidget::WinAim()
{
	PlayAnimation(Win1Aim);
	PlayAnimation(Win2Aim);
}
