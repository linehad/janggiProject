// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "JanggiGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class JANGGI_API AJanggiGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
private:
	UPROPERTY()
		bool bReadyClient;
	UPROPERTY()
		bool bReadyServer;
	UFUNCTION()
		void GameStart();
	UFUNCTION()
		void ReStart();

public:
	UFUNCTION()
		void SetReadyServer();
	UFUNCTION()
		void SetbReadyClient();

	UFUNCTION()
		void ReStartReadyServer();
	UFUNCTION()
		void ReStartbReadyClient(bool ready);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
		TSubclassOf<UUserWidget> MainWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
		TSubclassOf<UUserWidget> WaitingWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
		TSubclassOf<UUserWidget> TimerWidgetClass;
protected:
	virtual void BeginPlay() override;
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
