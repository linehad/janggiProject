// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectPositionUserWidget.h"
#include "JanggiPlayerController.h"
#include "JanggiGameStateBase.h"
#include "Board.h"
#include "SoundManager.h"

#include "Kismet/GameplayStatics.h"

#include <Components/TextBlock.h>
#include <Components/Button.h>
#include <Components/GridPanel.h>

void USelectPositionUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Controller = Cast<AJanggiPlayerController>(GetWorld()->GetFirstPlayerController());

	Start_Button->SetIsEnabled(false);
	Start_Button->OnClicked.AddDynamic(this, &USelectPositionUserWidget::StartButtonCallback);

	Select_Button1->OnClicked.AddDynamic(this, &USelectPositionUserWidget::SelectButton1_Callback);
	Select_Button2->OnClicked.AddDynamic(this, &USelectPositionUserWidget::SelectButton2_Callback);
	Select_Button3->OnClicked.AddDynamic(this, &USelectPositionUserWidget::SelectButton3_Callback);
	Select_Button4->OnClicked.AddDynamic(this, &USelectPositionUserWidget::SelectButton4_Callback);

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASoundManager::StaticClass(), OutActors);
	for (AActor* a : OutActors)
	{
		SoundManager = Cast<ASoundManager>(a);
	}
	OutActors.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AJanggiGameStateBase::StaticClass(), OutActors);
	for (AActor* a : OutActors)
	{
		JanggiState = Cast<AJanggiGameStateBase>(a);
	}
}

void USelectPositionUserWidget::StartButtonActivate()
{
	if (bSelect)
	{
		Start_Button->SetIsEnabled(true);
	}
}

// 누르고 상대가 준비 할 때가지 대기
void USelectPositionUserWidget::StartButtonCallback()
{
	SoundManager->PlaySound(ButtonClickSoundEffect, ButtonVol);
	TArray<AActor*> OutActors;
	ABoard* JanggiBoard = nullptr;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABoard::StaticClass(), OutActors);
	for (AActor* a : OutActors)
	{
		JanggiBoard = Cast<ABoard>(a);
	}

	Start_TextBlock->SetText(FText::FromString("Waiting"));
	Start_Button->SetIsEnabled(false);
	Select_Button1->SetVisibility(ESlateVisibility::HitTestInvisible);
	Select_Button2->SetVisibility(ESlateVisibility::HitTestInvisible);
	Select_Button3->SetVisibility(ESlateVisibility::HitTestInvisible);
	Select_Button4->SetVisibility(ESlateVisibility::HitTestInvisible);

	if (GetWorld()->GetFirstPlayerController()->GetLocalRole() == ROLE_Authority)
	{
		Controller->SetServerIsReady();
	}
	else if (GetWorld()->GetFirstPlayerController()->GetRemoteRole() == ROLE_Authority)
	{
		Controller->SetClientIsReady();
	}
}

void USelectPositionUserWidget::SelectButton1_Callback() // 마상마상
{
	SoundManager->PlaySound(ButtonClickSoundEffect, ButtonVol);
	Select_Button1->SetIsEnabled(false); Select_Button2->SetIsEnabled(true); Select_Button3->SetIsEnabled(true); Select_Button4->SetIsEnabled(true);
	bSelect = true;
	// 1 : 마, 2 : 상, 6 : 상, 7 : 마
	// 82 : 마, 83 : 상, 87 : 상 88 : 마
	// 이 위치만 바꾸면 됨
	if (GetWorld()->GetFirstPlayerController()->GetLocalRole() == ROLE_Authority)
	{
		Controller->SelectPosition(1, RedKnight); // 상을 마로 바꿈
		Controller->SelectPosition(6, RedKnight);
		Controller->SelectPosition(2, RedElephant); // 상을 마로 바꿈
		Controller->SelectPosition(7, RedElephant);
	}
	else if (GetWorld()->GetFirstPlayerController()->GetRemoteRole() == ROLE_Authority)
	{
		Controller->SelectPosition(83, BlueKnight); // 상을 마로 바꿈
		Controller->SelectPosition(88, BlueKnight);
		Controller->SelectPosition(82, BlueElephant); // 상을 마로 바꿈
		Controller->SelectPosition(87, BlueElephant);
	}
	StartButtonActivate();
}

void USelectPositionUserWidget::SelectButton2_Callback() // 상마상마
{
	// 1 : 마, 2 : 상, 6 : 상, 7 : 마
    // 82 : 마, 83 : 상, 87 : 상 88 : 마
    // 이 위치만 바꾸면 됨
	SoundManager->PlaySound(ButtonClickSoundEffect, ButtonVol);
	Select_Button1->SetIsEnabled(true); Select_Button2->SetIsEnabled(false); Select_Button3->SetIsEnabled(true); Select_Button4->SetIsEnabled(true);
	bSelect = true;
	if (GetWorld()->GetFirstPlayerController()->GetLocalRole() == ROLE_Authority)
	{
		Controller->SelectPosition(2, RedKnight); // 상을 마로 바꿈
		Controller->SelectPosition(7, RedKnight);
		Controller->SelectPosition(1, RedElephant); // 상을 마로 바꿈
		Controller->SelectPosition(6, RedElephant);
	}
	else if (GetWorld()->GetFirstPlayerController()->GetRemoteRole() == ROLE_Authority)
	{
		Controller->SelectPosition(82, BlueKnight); // 상을 마로 바꿈
		Controller->SelectPosition(87, BlueKnight);
		Controller->SelectPosition(83, BlueElephant); // 상을 마로 바꿈
		Controller->SelectPosition(88, BlueElephant);
	}
	StartButtonActivate();
}

void USelectPositionUserWidget::SelectButton3_Callback() // 마상상마
{
	// 1 : 마, 2 : 상, 6 : 상, 7 : 마
    // 82 : 마, 83 : 상, 87 : 상 88 : 마
    // 이 위치만 바꾸면 됨
	SoundManager->PlaySound(ButtonClickSoundEffect, ButtonVol);
	Select_Button1->SetIsEnabled(true); Select_Button2->SetIsEnabled(true); Select_Button3->SetIsEnabled(false); Select_Button4->SetIsEnabled(true);
	bSelect = true;
	if (GetWorld()->GetFirstPlayerController()->GetLocalRole() == ROLE_Authority)
	{
		Controller->SelectPosition(1, RedKnight); // 상을 마로 바꿈
		Controller->SelectPosition(7, RedKnight);
		Controller->SelectPosition(2, RedElephant); // 상을 마로 바꿈
		Controller->SelectPosition(6, RedElephant);
	}
	else if (GetWorld()->GetFirstPlayerController()->GetRemoteRole() == ROLE_Authority)
	{
		Controller->SelectPosition(82, BlueKnight); // 상을 마로 바꿈
		Controller->SelectPosition(88, BlueKnight);
		Controller->SelectPosition(83, BlueElephant); // 상을 마로 바꿈
		Controller->SelectPosition(87, BlueElephant);
	}
	StartButtonActivate();
}

void USelectPositionUserWidget::SelectButton4_Callback() // 상마마상
{
	// 1 : 마, 2 : 상, 6 : 상, 7 : 마
    // 82 : 마, 83 : 상, 87 : 상 88 : 마
    // 이 위치만 바꾸면 됨
	SoundManager->PlaySound(ButtonClickSoundEffect, ButtonVol);
	Select_Button1->SetIsEnabled(true); Select_Button2->SetIsEnabled(true); Select_Button3->SetIsEnabled(true); Select_Button4->SetIsEnabled(false);
	bSelect = true;
	if (GetWorld()->GetFirstPlayerController()->GetLocalRole() == ROLE_Authority)
	{
		Controller->SelectPosition(2, RedKnight); // 상을 마로 바꿈
		Controller->SelectPosition(6, RedKnight);
		Controller->SelectPosition(1, RedElephant); // 상을 마로 바꿈
		Controller->SelectPosition(7, RedElephant);
	}
	else if (GetWorld()->GetFirstPlayerController()->GetRemoteRole() == ROLE_Authority)
	{
		Controller->SelectPosition(83, BlueKnight); // 상을 마로 바꿈
		Controller->SelectPosition(87, BlueKnight);
		Controller->SelectPosition(82, BlueElephant); // 상을 마로 바꿈
		Controller->SelectPosition(88, BlueElephant);
	}
	StartButtonActivate();
}