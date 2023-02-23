// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialController.h"
#include "PowerAndHealthWidget.h"

#include <Blueprint/UserWidget.h>
void ATutorialController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;
	// SetInputMode�� FInputModeGameAndUI�� �־�θ� ���Ӱ� UI��� �Է��� ������ ���°� �ȴ�.
	SetInputMode(FInputModeGameAndUI());
	ChangeWidget(StartingWidgetClass);
	if (ShowPowerHealthClass != nullptr)
	{
		ShowPowerHealthWidget = CreateWidget(GetWorld(), ShowPowerHealthClass);
		if (ShowPowerHealthWidget != nullptr)
		{
			ShowPowerHealthWidget->AddToViewport();
		}
	}
}

void ATutorialController::ChangeWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
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

void ATutorialController::ShowPowerHealth(int32 pieciesIndex, int32 power, int32 health)
{
	Cast<UPowerAndHealthWidget>(ShowPowerHealthWidget)->ShowPowerHealth(pieciesIndex, power, health);
}