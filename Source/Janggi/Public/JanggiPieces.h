// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
enum PieciesEnum
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
class JANGGI_API JanggiPieces
{
private:
	const int PALACE_X_STARTING__POINT = 3;
	const int PALACE_X_END__POINT = 5;
	const int X_SIZE = 9; // ���� ũ�� 9
	const int Y_SIZE = 10; // ���� ũ�� 10
	const int DIRECTION = 4;
	const int DIAGONAL_DIRECTION = 2;
	const int BOARD_SIZE = X_SIZE * Y_SIZE;
	const int EmptyHere = 0;
	const int RED_TEAM = 7; // �ѳ������� �ʳ������� ������ ���

	// ���ʺ��� �ݽð� ���� ���� Ž��(�����Ͽ� ��, ��, ��, ���� ���� �迭)
	const int32 straightX[4] = { 0, -1, 0, 1 };
	const int32 straightY[4] = { 1, 0, -1, 0 };

	// ���� ������ �ݽð� ���� �밢�� Ž��(�»�, ����, ����, ��� ��, ���� ���� �迭 straightX, straightY�� �¹����鼭 ���ư���.)
	const int32 diagonalX[4] = { -1, -1, 1, 1 };
	const int32 diagonalY[4] = { 1, -1, -1, 1 };

	bool IsMove(const TArray<int32>& boardIndexArr, int32 xIndex, int32 yIndex, int32 curPos); // ���� ���� ���� �ѳ������� �ʳ������� �Ǻ��� ���� ���� �⹰�̸� �̵��� �����ϴ� �Լ�
	bool CheckEnemy(const TArray<int32>& boardIndexArr, int32 xIndex, int32 yIndex, int32 curPos); // ���� �� ó�� ���� �̵��ϴ� �⹰�� ��븦 ������ ���ߴ� �Լ�
public:
	TArray<int32>Rook(int32 xIndex, int32 yIndex, const TArray<int32>& boardIndexArr, int32 PalaceYCenter, int32 PalaceStartingPoint, int32 PalaceEndPoint);
	TArray<int32>Knight(int32 xIndex, int32 yIndex, const TArray<int32>& boardIndexArr);
	TArray<int32>Elephant(int32 xIndex, int32 yIndex, const TArray<int32>& boardIndexArr);
	TArray<int32>GuardsAndKing(int32 xIndex, int32 yIndex, const TArray<int32>& boardIndexArr, int32 PalaceYCenter, int32 PalaceStartingPoint, int32 PalaceEndPoint);
	TArray<int32>Cannon(int32 xIndex, int32 yIndex, const TArray<int32>& boardIndexArr, int32 PalaceYCenter, int32 PalaceStartingPoint, int32 PalaceEndPoint, int32 pos);
	TArray<int32>Pawn(int32 xIndex, int32 yIndex, const TArray<int32>& boardIndexArr, int32 pawnStartDirection, int32 pawnEndDirection, int32 PalaceYCenter, int32 PalaceStartingPoint, int32 PalaceEndPoint);
};

inline int32 Board_index(int x, int y) 
{
	const int XSize = 9; 
	return (XSize * y) + x; // 2���� �迭ó�� �������� ��
} 