// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SoundManager.generated.h"

enum
{
	WaitingBGM = 0,
	JanggiMapBGM,
	ButtonClickSoundEffect,
	SelectPieciesSoundEffect,
	PutPieciesSoundEffect,
	LoseSoundEffect,
	LoseBGM,
	WinSoundEffect,
	WinBGM,
	SelectBGM,
	TurnSoundEffect,
	NoSkillSoundEffect,
};

UCLASS()
class JANGGI_API ASoundManager : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
		TArray<class USoundWave*> SoundBase;
public:	
	// Sets default values for this actor's properties
	ASoundManager();

	void PlaySound(int32 SoundNum, float volume);
	void StopSound(int32 SoundNum);
	void LoopingSound(int32 SoundNum);
};
