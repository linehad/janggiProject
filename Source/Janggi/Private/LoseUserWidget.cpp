// Fill out your copyright notice in the Description page of Project Settings.


#include "LoseUserWidget.h"
#include "SoundManager.h"
#include "JanggiPlayerController.h"

#include "Components/TextBlock.h"
#include <Components/Button.h>
#include "Animation/WidgetAnimation.h"

#include "Kismet/GameplayStatics.h"
void ULoseUserWidget::NativeConstruct()
{
	EndButton->OnClicked.AddDynamic(this, &ULoseUserWidget::EndButtonCallback);
	MainButton->OnClicked.AddDynamic(this, &ULoseUserWidget::CallBack_MainButton);
	ReStartButton->OnClicked.AddDynamic(this, &ULoseUserWidget::CallBack_ReStartButton);

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASoundManager::StaticClass(), OutActors);
	for (AActor* a : OutActors)
	{
		SoundManager = Cast<ASoundManager>(a);
	}
}

void ULoseUserWidget::TimeOut()
{
	LoseTextBlock->SetVisibility(ESlateVisibility::Hidden);
	TimeLoseTextBlock->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void ULoseUserWidget::EndButtonCallback()
{
	Cast<AJanggiPlayerController>(GetWorld()->GetFirstPlayerController())->ReStartReadyClient(false);
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}

void ULoseUserWidget::CallBack_MainButton()
{
	Cast<AJanggiPlayerController>(GetWorld()->GetFirstPlayerController())->ReStartReadyClient(false);
}

void ULoseUserWidget::LoseAim()
{
	PlayAnimation(loseAim);
}

void ULoseUserWidget::CallBack_ReStartButton()
{
	SoundManager->StopSound(LoseBGM);
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