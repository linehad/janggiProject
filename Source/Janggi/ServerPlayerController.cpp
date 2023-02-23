// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include <Blueprint/UserWidget.h>

void AServerPlayerController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;
	// SetInputMode�� FInputModeGameAndUI�� �־�θ� ���Ӱ� UI��� �Է��� ������ ���°� �ȴ�.
	SetInputMode(FInputModeUIOnly ());
}

void AServerPlayerController::ChangeWidget(TSubclassOf<UUserWidget> NewWidgetClass)
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