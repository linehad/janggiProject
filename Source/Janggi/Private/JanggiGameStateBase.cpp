// Fill out your copyright notice in the Description page of Project Settings.


#include "JanggiGameStateBase.h"
#include "JanggiPlayerController.h"
#include "JanggiFunction.h"

#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"

AJanggiGameStateBase::AJanggiGameStateBase()
{
	bReplicates = true;

	ResetArr();
}

void AJanggiGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AJanggiGameStateBase, gameTurn);
	DOREPLIFETIME(AJanggiGameStateBase, lastTurn);
	DOREPLIFETIME(AJanggiGameStateBase, position);
	DOREPLIFETIME(AJanggiGameStateBase, bSkillUsing);
}

bool AJanggiGameStateBase::AttackPiecies(int32 curPosition, int32 lastClick)
{
	int pieciesHealth = healthATKArr[curPosition];
	resurrectPos = -1;
	healthATKArr[curPosition] = Attack(healthATKArr, boardIndexArr, curPosition, lastClick);

	if (pieciesHealth != healthATKArr[curPosition]) // 공격 당했다면
	{
		bIsAttack = true;
	}
	else // 공격 당하지 않았다면
	{
		bIsAttack = false;
	}

	if (boardIndexArr[curPosition] == RedKing && healthATKArr[curPosition] <= 0) // 공격 지점이 한나라 왕이고 왕의 체력이 0이 되었을 때 실행
	{
		UE_LOG(LogTemp, Error, TEXT("RedKing Die"));
		Cast<AJanggiPlayerController>(GetWorld()->GetFirstPlayerController())->GameOver(false, Blue);
		return true; // 왕 파괴
	}

	else if (boardIndexArr[curPosition] == BlueKing && healthATKArr[curPosition] <= 0) // 공격 지점이 초나라 왕이고 왕의 체력이 0이 되었을 때 실행
	{
		UE_LOG(LogTemp, Error, TEXT("BlueKing Die"));
		Cast<AJanggiPlayerController>(GetWorld()->GetFirstPlayerController())->GameOver(false, Red);
		return true; // 왕 파괴
	}

	else if (healthATKArr[curPosition] <= 0) // 적 체력이 0인지 확인
	{
		const int Y_SIZE = 9; // 세로 크기 0 부터 9

		int32 resurrectPosition = curPosition;

		int32 y = GetY(curPosition);
		int32 x = GetX(y, curPosition);

		switch (boardIndexArr[curPosition])
		{
		case RedPawn: // 졸 들은 한칸 뒤에서 부활하고 사는 제자리 부활한다.
			if (y > 0)
			{
				y--;
				resurrectPosition = GetBoardIndex(x, y);
			}
			AddResurrectionPieces(curPosition, resurrectPosition, Pawn_ResurrectTurn);
			break;
		case BluePawn:
			if (y < Y_SIZE)
			{
				y++;
				resurrectPosition = GetBoardIndex(x, y);
			}
			AddResurrectionPieces(curPosition, resurrectPosition, Pawn_ResurrectTurn);
			break;
		case RedGuards:
		case BlueGuards:
			AddResurrectionPieces(curPosition, resurrectPosition, Guards_ResurrectTurn);
		default:
			break;
		}
	
		return true; // 파괴해야 하면 true 반환
	}

	return false;
}

void AJanggiGameStateBase::MoveArr(int32 curPosition, int32 lastClick)
{
	boardIndexArr[curPosition] = boardIndexArr[lastClick];
	boardIndexArr[lastClick] = 0;

	healthATKArr[curPosition] = healthATKArr[lastClick];
	healthATKArr[lastClick] = 0;
}

void AJanggiGameStateBase::WidgetSelectPosition(int32 pos, int32 pieces)
{
	boardIndexArr[pos] = pieces;
}

void AJanggiGameStateBase::OnRep_position()
{
	GetPosition();
}

void AJanggiGameStateBase::OnRep_bSkillUsing()
{
	GetSkillUsing();
}

void AJanggiGameStateBase::AddResurrectionPieces(int32 curPosition, int32 resurrectPosition, int32 resurrectTurn)
{
	TMap<int32, int32> temp;
	temp.Empty();
	temp.Add(boardIndexArr[curPosition], resurrectPosition);

	resurrectionPos.Add(temp); // Key = 부활 할 말, value : 부활 장소
	resurrectionTurn.Add(resurrectTurn); // 부활 턴
}

bool AJanggiGameStateBase::Resurrection() // 부활 시킵니다.
{
	for (int i = 0; i < resurrectionPos.Num(); i++)
	{
		resurrectionTurn[i]--;
		if (resurrectionTurn[i] <= 0)
		{
			resurrectionTurn.Remove(i);
			resurrectPos = resurrectionPos[i].begin().Value();
			int32 resurrectPieces = resurrectionPos[i].begin().Key();

			if (boardIndexArr[resurrectPos] == RedKing) // 부활 위치에 한나라 왕이 있다면
			{
				UE_LOG(LogTemp, Error, TEXT("RedKing Die"));
				Cast<AJanggiPlayerController>(GetWorld()->GetFirstPlayerController())->GameOver(false, Blue);
			}
			else if (boardIndexArr[resurrectPos] == BlueKing) // 부활 위치에 초나라 왕이 있다면
			{
				UE_LOG(LogTemp, Error, TEXT("BlueKing Die"));
				Cast<AJanggiPlayerController>(GetWorld()->GetFirstPlayerController())->GameOver(false, Red);
			}
			boardIndexArr[resurrectPos] = resurrectPieces;
			healthATKArr[resurrectPos] = 14;
			resurrectionPos.RemoveAt(i);
			return true;
		}
	}
	return false;
}

void AJanggiGameStateBase::ResetArr()
{
	// 각 말들의 체력 초기화 나중에 Swhich 문으로 말마다 체력을 정해주는 것도 가능하다.
	resurrectionPos.Empty();
	resurrectionTurn.Empty();
	healthATKArr.Empty();
	boardIndexArr.Empty();

	boardIndexArr = resetBoard;
	for (int i = 0; i < boardIndexArr.Num(); i++)
	{
		if (boardIndexArr[i] != EmptyHere)
		{
			healthATKArr.Add(PieciesHealth);
		}
		else
		{
			healthATKArr.Add(EmptyHere);
		}
	}
}
