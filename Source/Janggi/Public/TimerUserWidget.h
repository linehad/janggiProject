// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimerUserWidget.generated.h"

UCLASS()
class JANGGI_API UTimerUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	int32 myMinute = 15;
	int32 mySeconds = 0;

	int32 enemyMinute = 15;
	int32 enemySeconds = 0;
	int32 myTurn = 0;
	void CountDown();

	FTimerHandle timerHandle;

	class AJanggiGameStateBase* JanggiState;
	class ASoundManager* SoundManager = nullptr;
private:
	void CountMyTime();
	void CountEnemyTime();

	UFUNCTION()
	void SkillButtonCallback();
protected:
	UPROPERTY(meta = (BindWidget))
		class UButton* SkillButton = nullptr;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TurnTextBlock = nullptr;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* MyMinuteTextBlock = nullptr;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* MySecondsTextBlock = nullptr;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* EnemyMinuteTextBlock = nullptr;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* EnemySecondsTextBlock = nullptr;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* SkillTextBlock = nullptr;


	UPROPERTY(Transient, meta = (BindWidgetAnim))
		class UWidgetAnimation* TurnAim = nullptr;

	virtual void NativeConstruct() override;
public:
	UFUNCTION()
		void StartTimer();
	UFUNCTION()
		void EndTimer();
	UFUNCTION()
		void CountTurn(bool turn);
	UFUNCTION()
		void ResetMyturn();
	UFUNCTION()
		void SetSkillCount(int32 count);
};
