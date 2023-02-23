// Fill out your copyright notice in the Description page of Project Settings.


#include "JanggiFunction.h"
#include "JanggiPieces.h"
#include "PiecesSkill.h"

TArray<int32> CheckMove(const TArray<int32>& boardIndexArr, int32 pos, int32 turn)
{

	const int Y_SIZE = 10; // 세로 크기 10
	JanggiPieces Pieces;

	int curPos = 0;
	int PalaceYCenter = 1;
	int PalaceStartingPoint = 0;
	int PalaceEndPoint = 2;
	int pawnStartDirection = 0;
	int pawnEndDirection = 3;
	TArray<int32> possibleMove; // 이동 가능한 곳을 리턴하기 위한 Tarray
	possibleMove.Empty();

	int yIndex = GetY(pos);
	int xIndex = GetX(yIndex, pos);

	if (yIndex > PalaceEndPoint)
	{
		PalaceYCenter = (Y_SIZE - 1) - PalaceYCenter; // 현재 위치가 한나라 궁 범위보다 크면 센터를 초나라로 잡아준다
		int temp = PalaceStartingPoint;
		PalaceStartingPoint = (Y_SIZE - 1) - PalaceEndPoint;
		PalaceEndPoint = (Y_SIZE - 1) - temp;
	}
	if (turn == Blue)
	{
		switch (boardIndexArr[pos])
		{
		case BlueRook:
			possibleMove = Pieces.Rook(xIndex, yIndex, boardIndexArr, PalaceYCenter, PalaceStartingPoint, PalaceEndPoint);
			break;

		case BlueKnight:
			possibleMove = Pieces.Knight(xIndex, yIndex, boardIndexArr);
			break;

		case BlueElephant:
			possibleMove = Pieces.Elephant(xIndex, yIndex, boardIndexArr);
			break;

		case BlueGuards:
		case BlueKing:
			possibleMove = Pieces.GuardsAndKing(xIndex, yIndex, boardIndexArr, PalaceYCenter, PalaceStartingPoint, PalaceEndPoint);
			break;

		case BlueCannon:
			possibleMove = Pieces.Cannon(xIndex, yIndex, boardIndexArr, PalaceYCenter, PalaceStartingPoint, PalaceEndPoint, pos);
			break;

		case BluePawn:
			pawnStartDirection++;
			pawnEndDirection++;
			possibleMove = Pieces.Pawn(xIndex, yIndex, boardIndexArr, pawnStartDirection, pawnEndDirection, PalaceYCenter, PalaceStartingPoint, PalaceEndPoint);
			break;

		default:
			break;
		}
	}
	
	else
	{
		switch (boardIndexArr[pos])
		{
		case RedRook:
			possibleMove = Pieces.Rook(xIndex, yIndex, boardIndexArr, PalaceYCenter, PalaceStartingPoint, PalaceEndPoint);
			break;

		case RedKnight:
			possibleMove = Pieces.Knight(xIndex, yIndex, boardIndexArr);
			break;

		case RedElephant:
			possibleMove = Pieces.Elephant(xIndex, yIndex, boardIndexArr);
			break;

		case RedGuards:
		case RedKing:
			possibleMove = Pieces.GuardsAndKing(xIndex, yIndex, boardIndexArr, PalaceYCenter, PalaceStartingPoint, PalaceEndPoint);
			break;

		case RedCannon:
			possibleMove = Pieces.Cannon(xIndex, yIndex, boardIndexArr, PalaceYCenter, PalaceStartingPoint, PalaceEndPoint, pos);
			break;

		case RedPawn:
			possibleMove = Pieces.Pawn(xIndex, yIndex, boardIndexArr, pawnStartDirection, pawnEndDirection, PalaceYCenter, PalaceStartingPoint, PalaceEndPoint);
			break;

		default:
			break;
		}
	}
	
	return possibleMove;
}

TArray<int32> CheckSkillMove(const TArray<int32>& boardIndexArr, int32 pos, int32 turn)
{
	PiecesSkill Pieces;
	const int Y_SIZE = 10; // 세로 크기 10

	int curPos = 0;
	int PalaceYCenter = 1;
	int PalaceStartingPoint = 0;
	int PalaceEndPoint = 2;

	TArray<int32> possibleMove; // 이동 가능한 곳을 리턴하기 위한 Tarray
	possibleMove.Empty();

	int yIndex = GetY(pos);
	int xIndex = GetX(yIndex, pos);

	if (yIndex > PalaceEndPoint)
	{
		PalaceYCenter = (Y_SIZE - 1) - PalaceYCenter; // 현재 위치가 한나라 궁 범위보다 크면 센터를 초나라로 잡아준다
		int temp = PalaceStartingPoint;
		PalaceStartingPoint = (Y_SIZE - 1) - PalaceEndPoint;
		PalaceEndPoint = (Y_SIZE - 1) - temp;
	}
	if (turn == Blue)
	{
		switch (boardIndexArr[pos])
		{
		case BlueRook:
			//possibleMove = Pieces.Rook(xIndex, yIndex, boardIndexArr, PalaceYCenter, PalaceStartingPoint, PalaceEndPoint);
			break;

		case BlueKnight:
			possibleMove = Pieces.Knight(xIndex, yIndex, boardIndexArr, PalaceYCenter, PalaceStartingPoint, PalaceEndPoint);
			break;

		case BlueElephant:
			possibleMove = Pieces.Elephant(xIndex, yIndex, boardIndexArr);
			break;

		case BlueGuards:
		case BlueKing:
			//possibleMove = Pieces.GuardsAndKing(xIndex, yIndex, boardIndexArr, PalaceYCenter, PalaceStartingPoint, PalaceEndPoint);
			break;

		case BlueCannon:
			//possibleMove = Pieces.Cannon(xIndex, yIndex, boardIndexArr, PalaceYCenter, PalaceStartingPoint, PalaceEndPoint, pos);
			break;

		case BluePawn:

			possibleMove = Pieces.Pawn(xIndex, yIndex, boardIndexArr);
			break;

		default:
			break;
		}
	}

	else
	{
		switch (boardIndexArr[pos])
		{
		case RedRook:
			//possibleMove = Pieces.Rook(xIndex, yIndex, boardIndexArr, PalaceYCenter, PalaceStartingPoint, PalaceEndPoint);
			break;

		case RedKnight:
			possibleMove = Pieces.Knight(xIndex, yIndex, boardIndexArr, PalaceYCenter, PalaceStartingPoint, PalaceEndPoint);
			break;

		case RedElephant:
			possibleMove = Pieces.Elephant(xIndex, yIndex, boardIndexArr);
			break;

		case RedGuards:
		case RedKing:
			//possibleMove = Pieces.GuardsAndKing(xIndex, yIndex, boardIndexArr, PalaceYCenter, PalaceStartingPoint, PalaceEndPoint);
			break;

		case RedCannon:
			//possibleMove = Pieces.Cannon(xIndex, yIndex, boardIndexArr, PalaceYCenter, PalaceStartingPoint, PalaceEndPoint, pos);
			break;

		case RedPawn:
			possibleMove = Pieces.Pawn(xIndex, yIndex, boardIndexArr);
			break;

		default:
			break;
		}
	}

	return possibleMove;
}

int32 Attack(TArray<int32>& healthATKArr, TArray<int32>& boardIndexArr, int32 curPosition, int32 lastClick)
{

	if (boardIndexArr[curPosition] <= 0) // 비어 있으면 파괴 판정 리턴
	{
		return 0;
	}
	
	// 비어 있지 않으면 공격연산 시작
	switch (boardIndexArr[lastClick])
	{
	case RedRook:
	case BlueRook:
		healthATKArr[curPosition] -= RookPower;
		break;
	case RedKnight:
	case BlueKnight:
		healthATKArr[curPosition] -= KnightPower;
		break;
	case RedElephant:
	case BlueElephant:
		healthATKArr[curPosition] -= ElephantPower;
		break;
	case RedGuards:
	case BlueGuards:
		healthATKArr[curPosition] -= GuardsPower;
		break;
	case RedKing:
	case BlueKing:
		healthATKArr[curPosition] -= KingPower;
		break;
	case RedCannon:
	case BlueCannon:
		healthATKArr[curPosition] -= CannonPower;
		break;
	case RedPawn:
	case BluePawn:
		healthATKArr[curPosition] -= PawnPower;
		break;

	default:
		break;
	}

	return healthATKArr[curPosition];
}

int32 GetY(int32 pos)
{
	const int X_SIZE = 9;
	const int BOARD_SIZE = 90;
	int yIndexArr[90] = { 0, };
	int y = 0;
	// y값을 추론하기 위한 배열 정의
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if (i != 0 && i % X_SIZE == 0)
		{
			y++;
		}
		yIndexArr[i] = y;
	}

	return  yIndexArr[pos];
}

int32 GetX(int32 y, int32 pos)
{
	const int Y_SIZE = 10;
	int x = -1;
	// x값 추론
	for (int i = 0; i < Y_SIZE; i++)
	{
		if (GetBoardIndex(i, y) == pos)
		{
			x = i;
			break;
		}
	}
	return x;
}

int32 GetPower(int32 Piecies)
{
	int32 pieciesPower = 0;
	switch (Piecies)
	{
	case RedRook:
	case BlueRook:
		pieciesPower = RookPower;
		break;
	case RedKnight:
	case BlueKnight:
		pieciesPower = KnightPower;
		break;
	case RedElephant:
	case BlueElephant:
		pieciesPower = ElephantPower;
		break;
	case RedGuards:
	case BlueGuards:
		pieciesPower = GuardsPower;
		break;
	case RedKing:
	case BlueKing:
		pieciesPower = KingPower;
		break;
	case RedCannon:
	case BlueCannon:
		pieciesPower = CannonPower;
		break;
	case RedPawn:
	case BluePawn:
		pieciesPower = PawnPower;
		break;

	default:
		break;
	}
	return pieciesPower;
}

int32 GetPiecies(int32 Piecies)
{
	int32 PieciesName = 0;
	switch (Piecies)
	{
	case RedRook:
	case BlueRook:
		PieciesName = 1;
		break;
	case RedKnight:
	case BlueKnight:
		PieciesName = 2;
		break;
	case RedElephant:
	case BlueElephant:
		PieciesName = 3;
		break;
	case RedGuards:
	case BlueGuards:
		PieciesName = 4;
		break;
	case RedKing:
		PieciesName = 5;
		break;
	case BlueKing:
		PieciesName = 6;
		break;
	case RedCannon:
	case BlueCannon:
		PieciesName = 7;
		break;
	case RedPawn:
	case BluePawn:
		PieciesName = 8;
		break;

	default:
		break;
	}
	return PieciesName;
}
