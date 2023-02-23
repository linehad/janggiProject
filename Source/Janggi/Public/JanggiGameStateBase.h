// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "JanggiGameStateBase.generated.h"

enum Piecies
{
	EmptyHere = 0,
	RedRook,
	RedKnight,
	RedElephant,
	RedGuards,
	RedKing,
	RedCannon,
	RedPawn,
	BlueRook,
	BlueKnight,
	BlueElephant,
	BlueGuards,
	BlueKing,
	BlueCannon,
	BluePawn
};

/**
 * 
 */
UCLASS()
class JANGGI_API AJanggiGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
private:
	const int Pawn_ResurrectTurn = 30;
	const int Guards_ResurrectTurn = 20;
	int32 resurrectPos = -1;
	bool bIsAttack = false;

protected:
	// 게임턴 1 한나라 2 초나라
	UPROPERTY(Replicated)
	int16 gameTurn = 2; // 현재 진행해야 하는 게임턴
	UPROPERTY(Replicated)
	int16 lastTurn = 1; // 마지막으로 진행된 게임턴

	UPROPERTY(ReplicatedUsing= OnRep_bSkillUsing)
		bool bSkillUsing = false;

	UPROPERTY(ReplicatedUsing = OnRep_position) // 블루프린트 컨트롤러에서 RPC를 위해서 사용
	int16 position = 0;
	UFUNCTION()
	void OnRep_position();
	UFUNCTION()
	void OnRep_bSkillUsing();
	
private:
	void AddResurrectionPieces(int32 curPosition,  int32 resurrectPosition, int32 resurrectTurn);
public:
	AJanggiGameStateBase();
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void SetGameTurn(int32 Turn) { gameTurn = Turn; }

	void SetlastTurn(int32 Turn) { lastTurn = Turn; }

	UFUNCTION(BlueprintCallable, Category = "BoardVal")
		void SetPosition(int32 curPosition) { position = curPosition; }
	UFUNCTION(BlueprintCallable, Category = "BoardVal")
		int32 GetPosition() { return position; }
	UFUNCTION(BlueprintCallable, Category = "BoardVal")
	int32 GetGameTurn() { return gameTurn; }
	UFUNCTION(BlueprintCallable, Category = "BoardVal")
	int32 GetLastTurn() { return lastTurn; }
	UFUNCTION()
		bool AttackPiecies(int32 curPosition, int32 lastClick);

	// 말 위치 이동 관련
	UFUNCTION()
		void MoveArr(int32 curPosition, int32 lastClick);
	UFUNCTION()
		void WidgetSelectPosition(int32 pos, int32 pieces);

	UFUNCTION(BlueprintCallable, Category = "BoardVal")
	const TArray<int32> &GetBoardIndexArr() const { return boardIndexArr; }

	UFUNCTION(BlueprintCallable, Category = "BoardVal")
		int32 GetResurrectPos(){ return resurrectPos; }

	UFUNCTION()
		const TArray<int32>& GetHealthATKArr() const { return healthATKArr; }

	UFUNCTION()
	bool Resurrection();
	UFUNCTION()
		void ResetBoard() { boardIndexArr = resetBoard; }
	UFUNCTION()
		void ResetArr();
	bool GetIsAttack() { return bIsAttack; }
	void SetSkillUsing(bool IsSkill) { bSkillUsing = IsSkill; }
	bool GetSkillUsing() { return bSkillUsing; }
private:
	// 보드의 말 위치를 초기화한다. 배치는 거의 고정되어 있기 때문에 
	// 다시하기를 위해서 변경되지 않는 초기배치 resetBoard를 선언하고 boardIndexArr에 대입하는 형태로 작성한다.
	// 다만 체력의 경우 값이 늘어나거나 줄어드는 등 변경될 가능성이 있기에 따로 지정한다.
	const TArray<int32> resetBoard =
	{
		1, 2, 3, 4, 0, 4, 3, 2, 1,
		0, 0, 0, 0, 5, 0, 0, 0, 0,
		0, 6, 0, 0, 0, 0, 0, 6, 0,
		7, 0, 7, 0, 7, 0, 7, 0, 7,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		14, 0, 14, 0, 14, 0, 14, 0, 14,
		0, 13, 0, 0, 0, 0, 0, 13, 0,
		0, 0, 0, 0, 12, 0, 0, 0, 0,
		8, 9, 10, 11, 0, 11, 10, 9, 8 };

	UPROPERTY()
		TArray<int32> boardIndexArr;

	TArray<int32> healthATKArr;

	TArray<TMap<int32, int32>> resurrectionPos; // key 유닛 value 부활 위치
	TArray<int32> resurrectionTurn;
};
