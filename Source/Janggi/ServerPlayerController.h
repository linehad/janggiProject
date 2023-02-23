// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ServerPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class JANGGI_API AServerPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
		TSubclassOf<UUserWidget> StartWidget;

	UPROPERTY()
		UUserWidget* CurrentWidget;
		void ChangeWidget(TSubclassOf<UUserWidget> NewWidgetClass);
};
