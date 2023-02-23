// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WinUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class JANGGI_API UWinUserWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* WinTextBlock = nullptr;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TimeWinTextBlock = nullptr;

	UPROPERTY(meta = (BindWidget))
		class UButton* EndButton = nullptr;
	UPROPERTY(meta = (BindWidget))
		class UButton* MainButton = nullptr;
	UPROPERTY(meta = (BindWidget))
		class UButton* ReStartButton = nullptr;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
		class UWidgetAnimation* Win1Aim = nullptr;
	UPROPERTY(Transient, meta = (BindWidgetAnim))
		class UWidgetAnimation* Win2Aim = nullptr;

	class ASoundManager* SoundManager = nullptr;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
		TSubclassOf<UUserWidget> WaitingWidgetClass = nullptr;
public:
	virtual void NativeConstruct() override;
	void TimeOut();
	UFUNCTION()
		void EndButtonCallback();
	UFUNCTION()
		void CallBack_MainButton();
	UFUNCTION()
		void CallBack_ReStartButton();

	UFUNCTION()
		void WinAim();
};
