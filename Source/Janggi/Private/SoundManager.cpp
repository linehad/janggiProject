// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundManager.h"
#include "Sound/SoundWave.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ASoundManager::ASoundManager()
{
	SoundBase.Empty();

	static ConstructorHelpers::FObjectFinder<USoundWave> BGM0(TEXT("SoundWave'/Game/StarterContent/Audio/Waiting.Waiting'"));
	static ConstructorHelpers::FObjectFinder<USoundWave> BGM1(TEXT("SoundWave'/Game/StarterContent/Audio/JanggiMap.JanggiMap'"));
	static ConstructorHelpers::FObjectFinder<USoundWave> BGM2(TEXT("SoundWave'/Game/StarterContent/Audio/ButtonClick.ButtonClick'"));
	static ConstructorHelpers::FObjectFinder<USoundWave> BGM3(TEXT("SoundWave'/Game/StarterContent/Audio/SelectPiecies.SelectPiecies'"));
	static ConstructorHelpers::FObjectFinder<USoundWave> BGM4(TEXT("SoundWave'/Game/StarterContent/Audio/PutPiecies.PutPiecies'"));
	static ConstructorHelpers::FObjectFinder<USoundWave> BGM5(TEXT("SoundWave'/Game/StarterContent/Audio/Lose.Lose'"));
	static ConstructorHelpers::FObjectFinder<USoundWave> BGM6(TEXT("SoundWave'/Game/StarterContent/Audio/LoseBGM.LoseBGM'"));
	static ConstructorHelpers::FObjectFinder<USoundWave> BGM7(TEXT("SoundWave'/Game/StarterContent/Audio/Victory.Victory'"));
	static ConstructorHelpers::FObjectFinder<USoundWave> BGM8(TEXT("SoundWave'/Game/StarterContent/Audio/VictoryBGM.VictoryBGM'"));
	static ConstructorHelpers::FObjectFinder<USoundWave> BGM9(TEXT("SoundWave'/Game/StarterContent/Audio/SelectBGM.SelectBGM'"));
	static ConstructorHelpers::FObjectFinder<USoundWave> BGM10(TEXT("SoundWave'/Game/StarterContent/Audio/TurnSound.TurnSound'"));
	static ConstructorHelpers::FObjectFinder<USoundWave> BGM11(TEXT("SoundWave'/Game/StarterContent/Audio/NoSkill.NoSkill'"));

	if (BGM0.Succeeded())
	{
		SoundBase.Add(BGM0.Object);
	}
	if (BGM1.Succeeded())
	{
		SoundBase.Add(BGM1.Object);
	}
	if (BGM2.Succeeded())
	{
		SoundBase.Add(BGM2.Object);
	}
	if (BGM3.Succeeded())
	{
		SoundBase.Add(BGM3.Object);
	}
	if (BGM4.Succeeded())
	{
		SoundBase.Add(BGM4.Object);
	}
	if (BGM5.Succeeded())
	{
		SoundBase.Add(BGM5.Object);
	}
	if (BGM6.Succeeded())
	{
		SoundBase.Add(BGM6.Object);
	}
	if (BGM7.Succeeded())
	{
		SoundBase.Add(BGM7.Object);
	}
	if (BGM8.Succeeded())
	{
		SoundBase.Add(BGM8.Object);
	}
	if (BGM9.Succeeded())
	{
		SoundBase.Add(BGM9.Object);
	}
	if (BGM10.Succeeded())
	{
		SoundBase.Add(BGM10.Object);
	}
	if (BGM11.Succeeded())
	{
		SoundBase.Add(BGM11.Object);
	}
}

void ASoundManager::PlaySound(int32 SoundNum, float volume)
{
	SoundBase[SoundNum]->Volume = volume;
	UGameplayStatics::PlaySound2D(this, SoundBase[SoundNum]);
}

void ASoundManager::StopSound(int32 SoundNum)
{
	SoundBase[SoundNum]->bLooping = false;
	SoundBase[SoundNum]->Volume = 0.0f;
}

void ASoundManager::LoopingSound(int32 SoundNum)
{
	SoundBase[SoundNum]->bLooping = true;
}
