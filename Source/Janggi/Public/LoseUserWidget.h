// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoseUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class JANGGI_API ULoseUserWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* LoseTextBlock = nullptr;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TimeLoseTextBlock = nullptr;

	UPROPERTY(meta = (BindWidget))
		class UButton* EndButton = nullptr;
	UPROPERTY(meta = (BindWidget))
		class UButton* MainButton = nullptr;
	UPROPERTY(meta = (BindWidget))
		class UButton* ReStartButton = nullptr;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
		class UWidgetAnimation* loseAim = nullptr;

	class ASoundManager* SoundManager = nullptr;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
		TSubclassOf<UUserWidget> WaitingWidgetClass;

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
		void LoseAim();
};
