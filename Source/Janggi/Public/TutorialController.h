// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TutorialController.generated.h"

/**
 * 
 */
UCLASS()
class JANGGI_API ATutorialController : public APlayerController
{
	GENERATED_BODY()
protected:
	UPROPERTY()
		UUserWidget* ShowPowerHealthWidget = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
		TSubclassOf<UUserWidget> StartingWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
		TSubclassOf<UUserWidget> ShowPowerHealthClass;
public:
	virtual void BeginPlay() override;

	UPROPERTY()
		UUserWidget* CurrentWidget;

	void ChangeWidget(TSubclassOf<UUserWidget> NewWidgetClass);
	UFUNCTION()
		void ShowPowerHealth(int32 pieciesIndex, int32 power, int32 health);
};
