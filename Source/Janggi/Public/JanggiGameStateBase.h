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
	// ������ 1 �ѳ��� 2 �ʳ���
	UPROPERTY(Replicated)
	int16 gameTurn = 2; // ���� �����ؾ� �ϴ� ������
	UPROPERTY(Replicated)
	int16 lastTurn = 1; // ���������� ����� ������

	UPROPERTY(ReplicatedUsing= OnRep_bSkillUsing)
		bool bSkillUsing = false;

	UPROPERTY(ReplicatedUsing = OnRep_position) // �������Ʈ ��Ʈ�ѷ����� RPC�� ���ؼ� ���
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

	// �� ��ġ �̵� ����
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
	// ������ �� ��ġ�� �ʱ�ȭ�Ѵ�. ��ġ�� ���� �����Ǿ� �ֱ� ������ 
	// �ٽ��ϱ⸦ ���ؼ� ������� �ʴ� �ʱ��ġ resetBoard�� �����ϰ� boardIndexArr�� �����ϴ� ���·� �ۼ��Ѵ�.
	// �ٸ� ü���� ��� ���� �þ�ų� �پ��� �� ����� ���ɼ��� �ֱ⿡ ���� �����Ѵ�.
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

	TArray<TMap<int32, int32>> resurrectionPos; // key ���� value ��Ȱ ��ġ
	TArray<int32> resurrectionTurn;
};
