// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class JANGGI_API PiecesSkill
{
private:
	const int PALACE_X_STARTING__POINT = 3;
	const int PALACE_X_END__POINT = 5;
	const int X_SIZE = 9; // 가로 크기 9
	const int Y_SIZE = 10; // 세로 크기 10
	const int DIRECTION = 4;
	const int DIAGONAL_DIRECTION = 2;
	const int BOARD_SIZE = X_SIZE * Y_SIZE;
	const int EmptyHere = 0;
	const int RED_TEAM = 7; // 한나라인지 초나라인지 구별할 상수

	// 위쪽부터 반시계 방향 직선 탐색(상좌하우)
	const int32 straightX[4] = { 0, -1, 0, 1 };
	const int32 straightY[4] = { 1, 0, -1, 0 };

	// 왼쪽 위부터 반시계 방향 대각선 탐색(좌상, 좌하, 우하, 우상)
	const int32 diagonalX[4] = { -1, -1, 1, 1 };
	const int32 diagonalY[4] = { 1, -1, -1, 1 };

	bool IsMove(const TArray<int32>& boardIndexArr, int32 xIndex, int32 yIndex, int32 curPos); // 지금 눌린 돌이 한나라인지 초나라인지 판별후 같은 나라 기물이면 이동을 제한하는 함수
	bool CheckEnemy(const TArray<int32>& boardIndexArr, int32 xIndex, int32 yIndex, int32 curPos); // 차나 포 처럼 직선 이동하는 기물이 상대를 만나면 멈추는 함수
	inline int32 Board_index(int x, int y)
	{
		const int XSize = 9;
		return (XSize * y) + x; // 2차원 배열처럼 쓰기위한 식
	}
public:

	TArray<int32>Knight(int32 xIndex, int32 yIndex, const TArray<int32>& boardIndexArr, int32 PalaceYCenter, int32 PalaceStartingPoint, int32 PalaceEndPoint);
	TArray<int32>Pawn(int32 xIndex, int32 yIndex, const TArray<int32>& boardIndexArr);
	TArray<int32>Elephant(int32 xIndex, int32 yIndex, const TArray<int32>& boardIndexArr);
	PiecesSkill();

};