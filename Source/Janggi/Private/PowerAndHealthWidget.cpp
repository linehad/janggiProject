// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerAndHealthWidget.h"
#include "Components/TextBlock.h"

void UPowerAndHealthWidget::ShowPowerHealth(int32 pieciesIndex, int32 power, int32 health)
{
	PieciesTextBlock->SetText(FText::FromString(pieciesName[pieciesIndex]));
	PowerTextBlock->SetText(FText::FromString(FString::FromInt(power)));
	HealthTextBlock->SetText(FText::FromString(FString::FromInt(health)));
}