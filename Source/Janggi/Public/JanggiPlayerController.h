// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "JanggiPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class JANGGI_API AJanggiPlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	float JanggiMapBGMVol = 0.5f;
	bool bIsDestroy = false;
	int32 callCount = 0;
	UPROPERTY()
		UUserWidget* CurrentWidget = nullptr;
	UPROPERTY()
		UUserWidget* ShowPowerHealthWidget = nullptr;
	UPROPERTY()
		UUserWidget* WinnerWidget = nullptr;
	UPROPERTY()
		UUserWidget* LoserWidget = nullptr;
	class ASoundManager* SoundManager = nullptr;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
		TSubclassOf<UUserWidget> WaitingWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
		TSubclassOf<UUserWidget> LoseClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
		TSubclassOf<UUserWidget> WinClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
		TSubclassOf<UUserWidget> ShowPowerHealthClass;

	UPROPERTY(BlueprintReadWrite, Category = "BoardVal")
		class AJanggiGameStateBase* JanggiState = nullptr;
	UPROPERTY(BlueprintReadWrite, Category = "BoardVal")
		class ABoard* JanggiBoard = nullptr;

public:
	AJanggiPlayerController();
	virtual void BeginPlay() override;
	class ABoard* const GetJanggiBoard() { return JanggiBoard; }

	UFUNCTION()
		void ShowPowerHealth(int32 pieciesIndex, int32 power, int32 health);

	UFUNCTION()
		void SetServerIsReady();
	UFUNCTION()
		bool GetbIsDestroy() { return bIsDestroy; }

	UFUNCTION()
		void ResetMyturn();

	UFUNCTION(Server, Reliable)
		void SetClientIsReady();
	void SetClientIsReady_Implementation();

	/*위젯을 업데이트 하는 RPC 함수*/
	UFUNCTION(Client, Reliable)
		void ChangeWidget(TSubclassOf<UUserWidget> NewWidgetClass);
	void ChangeWidget_Implementation(TSubclassOf<UUserWidget> NewWidgetClass);

	UFUNCTION(Client, Reliable)
		void GameOver(bool timeOut, int32 winner);
	void GameOver_Implementation(bool timeOut, int32 winner);

	// 게임 시작을 알리는 함수
	UFUNCTION(Client, Reliable)
		void GameStart();
	void GameStart_Implementation();

	// 턴을 주고 받는 함수
	UFUNCTION(Server, Reliable)
		void SetGameTurn();
	void SetGameTurn_Implementation();

	UFUNCTION(Server, Reliable)
		void SetLastTurn();
	void SetLastTurn_Implementation();

	UFUNCTION(BlueprintCallable, Category = "BoardVal")
		void CountTurn(bool turn);

	UFUNCTION(Client, Reliable)
		void SetATK(int32 curPosition, int32 lastClick);
	void SetATK_Implementation(int32 curPosition, int32 lastClick);

	UFUNCTION(Server, Reliable)
		void SelectPosition(int32 pos, int32 pieces); // 기물 세팅 RPC 클라에서 서버로
	void SelectPosition_Implementation(int32 pos, int32 pieces);

	UFUNCTION(Client, Reliable)
		void SelectClientPosition(int32 pos, int32 pieces); // 기물 세팅 RPC 서버에서 클라로
	void SelectClientPosition_Implementation(int32 pos, int32 pieces);


	UFUNCTION(Server, Reliable)
		void ReStartReadyClient(bool ready); // 다시 시작 RPC 클라에서 서버로
	void ReStartReadyClient_Implementation(bool ready);
	UFUNCTION()
		void ReStartReadyServer(); // 다시 시작 RPC 서버에서 클라로

	UFUNCTION(Client, Reliable)
		void ServerMeue();
	void ServerMeue_Implementation();
	UFUNCTION(Client, Reliable)
		void PlayBGM(int32 StopBGM, int32 PlayBGM, float volume);
	void PlayBGM_Implementation(int32 StopBGM, int32 PlayBGM, float volume);

	UFUNCTION(Server, Reliable)
		void SetSkillUsing(bool IsSkill);
	void SetSkillUsing_Implementation(bool IsSkill);
	UFUNCTION()
	void ResetBoard();

	UFUNCTION()
		void RemoveResultWidget();
	UFUNCTION()
		void UsingSkill(int32 skillCount);
};
