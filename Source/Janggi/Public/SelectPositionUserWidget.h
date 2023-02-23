// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SelectPositionUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class JANGGI_API USelectPositionUserWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	float ButtonVol = 2.5f;

	const int RedKnight = 2;
	const int RedElephant = 3;
	const int BlueKnight = 9;
	const int BlueElephant = 10;

	bool bSelect = false;
	bool bReadyS = false;
	bool bReadyC = false;

	class AJanggiGameStateBase* JanggiState = nullptr;
	class AJanggiPlayerController* Controller = nullptr;
	class ASoundManager* SoundManager = nullptr;
public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
		void StartButtonActivate();

	UFUNCTION(BlueprintCallable)
		void StartButtonCallback();

	// 제한시간을 선택하는 버튼 바인드
	UPROPERTY(meta = (BindWidget))
		class UButton* Select_Button1 = nullptr;
	UPROPERTY(meta = (BindWidget))
		class UButton* Select_Button2 = nullptr;
	UPROPERTY(meta = (BindWidget))
		class UButton* Select_Button3 = nullptr;
	UPROPERTY(meta = (BindWidget))
		class UButton* Select_Button4 = nullptr;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Start_TextBlock = nullptr;
	// 상차림 선택 위젯 바인딩
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UGridPanel* SelectPosition_GridPanel = nullptr;

	UFUNCTION(BlueprintCallable)
		void SelectButton1_Callback();

	UFUNCTION(BlueprintCallable)
		void SelectButton2_Callback();

	UFUNCTION(BlueprintCallable)
		void SelectButton3_Callback();

	UFUNCTION(BlueprintCallable)
		void SelectButton4_Callback();


	// 시작버튼과 종료버튼 바인드
	UPROPERTY(meta = (BindWidget))
		class UButton* Start_Button = nullptr;
};
