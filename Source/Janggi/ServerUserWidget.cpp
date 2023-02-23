// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerUserWidget.h"
#include "ServerPlayerController.h"
#include <Components/Button.h>
#include <Components/EditableTextBox.h>
#include "Kismet/GameplayStatics.h"

void UServerUserWidget::NativeConstruct()
{
	ServerButton->OnClicked.AddDynamic(this, &UServerUserWidget::ServerButtonCallback);
	ClientButton->OnClicked.AddDynamic(this, &UServerUserWidget::ClientButtonCallback);
	Tutorial_Button->OnClicked.AddDynamic(this, &UServerUserWidget::TutorialButtonCallback);
	EndButton->OnClicked.AddDynamic(this, &UServerUserWidget::EndButtonCallback);

	ip_EditableTextBox->OnTextChanged.AddDynamic(this, &UServerUserWidget::IP_EditableTextBoxCallback);
}

void UServerUserWidget::ServerButtonCallback()
{
	UGameplayStatics::OpenLevel(this, FName(TEXT("JanggiMap")), true, FString(TEXT("listen")));
}

void UServerUserWidget::ClientButtonCallback()
{
	FName ip = FName(*ip_EditableTextBox->GetText().ToString());
	UGameplayStatics::OpenLevel(this, ip, true);
}

void UServerUserWidget::IP_EditableTextBoxCallback(const FText& Text)
{
	if (ip_EditableTextBox->GetText().ToString().Len() <= 0)
	{
		ClientButton->SetIsEnabled(false);
	}
	else {
		ClientButton->SetIsEnabled(true);
	}
}

void UServerUserWidget::TutorialButtonCallback()
{
	UGameplayStatics::OpenLevel(this, FName(TEXT("TutorialMap")));
}

void UServerUserWidget::EndButtonCallback()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}
