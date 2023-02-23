// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PowerAndHealthWidget.generated.h"

/**
 * 
 */
UCLASS()
class JANGGI_API UPowerAndHealthWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	TArray<FString> pieciesName =
	{
		FString(TEXT("없음")),
	    FString(TEXT("車")),
	    FString(TEXT("馬")),
	    FString(TEXT("象")),
	    FString(TEXT("士")),
	    FString(TEXT("韓")),
	    FString(TEXT("楚")),
    	FString(TEXT("包")),
		FString(TEXT("卒")),
	};
protected:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* PowerTextBlock = nullptr;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* HealthTextBlock = nullptr;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* PieciesTextBlock = nullptr;
public:
	UFUNCTION()
		void ShowPowerHealth(int32 pieciesIndex, int32 power, int32 health);
};
