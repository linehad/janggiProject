// Fill out your copyright notice in the Description page of Project Settings.


#include "PiecesSkill.h"

PiecesSkill::PiecesSkill()
{
}



TArray<int32> PiecesSkill::Knight(int32 xIndex, int32 yIndex, const TArray<int32>& boardIndexArr, int32 PalaceYCenter, int32 PalaceStartingPoint, int32 PalaceEndPoint)
{
	// 상하좌우로 움직여서 이동 가능한곳 체크
// 나중에 궁에 들어가면 대각선 이동 구현 해야함
	TArray<int32> possibleMove;
	possibleMove.Empty();

	for (int i = 0; i < DIRECTION; i++) // 모든 방향 탐색
	{
		int nx = xIndex;
		int ny = yIndex;
		int curPos = Board_index(nx, ny);
		bool bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);

		// 대각선 탐색
		if (curPos >= 0 && curPos < BOARD_SIZE && // 맵 바깥으로 나가지 말아야 하고
			(((xIndex == PALACE_X_STARTING__POINT || xIndex == PALACE_X_END__POINT) && (yIndex == PalaceStartingPoint || yIndex == PalaceEndPoint))) ||
			(xIndex == 4 && yIndex == PalaceYCenter)) // 궁의 가운데 또는 꼭짓점이여야 함)
		{
			nx = xIndex + diagonalX[i];
			ny = yIndex + diagonalY[i];
			curPos = Board_index(nx, ny);
			bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);
			// 대각선 탐색
			while (nx < X_SIZE && ny < Y_SIZE && nx >= 0 && ny >= 0 && curPos >= 0 && curPos < BOARD_SIZE && // 맵 바깥으로 나가지 말아야 하고
				nx >= PALACE_X_STARTING__POINT && nx <= PALACE_X_END__POINT && ny >= PalaceStartingPoint && ny <= PalaceEndPoint && // 궁 범위 안쪽이여야 하며
				bisMove) // 이동할 곳이 적이거나 비어있어야 함
			{
				if (nx >= X_SIZE || ny >= Y_SIZE && nx < 0 || ny < 0)break;
				else if (CheckEnemy(boardIndexArr, xIndex, yIndex, curPos))
				{
					possibleMove.Add(curPos);
					break;
				}
				possibleMove.Add(curPos);
				nx += diagonalX[i];
				ny += diagonalY[i];
				curPos = Board_index(nx, ny);
				bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);
			}
		}

		nx = xIndex + straightX[i];
		ny = yIndex + straightY[i];
		curPos = Board_index(nx, ny);
		bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);

		for (int j = 0; j < 2; j++)
		{
			if (nx < X_SIZE && ny < Y_SIZE && nx >= 0 && ny >= 0 &&
				curPos >= 0 && curPos < BOARD_SIZE &&
				bisMove) // curPos가 배열을 초과하지 않고 다음 이동할 위치가 비어있으면 이동이 가능하다.
			{

				if (nx >= X_SIZE || ny >= Y_SIZE && nx < 0 || ny < 0)break;
				else if (CheckEnemy(boardIndexArr, xIndex, yIndex, curPos))
				{
					possibleMove.Add(curPos);
					break;
				}
				possibleMove.Add(curPos);
				nx += straightX[i];
				ny += straightY[i];
				curPos = Board_index(nx, ny);
				bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);
			}
		}
	}
	return possibleMove;
}

TArray<int32> PiecesSkill::Pawn(int32 xIndex, int32 yIndex, const TArray<int32>& boardIndexArr)
{
	TArray<int32> possibleMove;
	possibleMove.Empty();

	int nx = xIndex;
	int ny = yIndex;
	int curPos = Board_index(nx, ny);

	for (int i = 0; i < DIRECTION; i++)
	{
		// 상좌하우 탐색
		nx = xIndex + straightX[i];
		ny = yIndex + straightY[i];
		curPos = Board_index(nx, ny);
		bool bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);
		if (nx < X_SIZE && ny < Y_SIZE && nx >= 0 && ny >= 0 && curPos >= 0 && curPos < BOARD_SIZE && // 맵 바깥으로 나가지 말아야 하고
			bisMove) // 이동할 곳이 비어있어야 한다.
		{
			possibleMove.Add(curPos);
		}

		nx = xIndex + diagonalX[i];
		ny = yIndex + diagonalY[i];
		curPos = Board_index(nx, ny);
		bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);
		// 대각선 탐색
		if (curPos >= 0 && curPos < BOARD_SIZE && // 맵 바깥으로 나가지 말아야 하고
			bisMove) // 이동할 곳이 비어있어야 한다.
		{
			possibleMove.Add(curPos);
		}
	}

	return possibleMove;
}

TArray<int32> PiecesSkill::Elephant(int32 xIndex, int32 yIndex, const TArray<int32>& boardIndexArr)
{
	TArray<int32> possibleMove;
	possibleMove.Empty();

	// 전진시 이동 가능한곳 체크
	int nx = xIndex + straightX[0];
	int ny = yIndex + straightY[0];
	int curPos = Board_index(nx, ny);
	bool bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);

	// 앞으로 한칸 이동했을 때 비어 있다면
	if (nx < X_SIZE && ny < Y_SIZE && nx >= 0 && ny >= 0 &&
		curPos >= 0 && curPos < BOARD_SIZE) // curPos가 배열을 초과하지 않으면 이동이 가능하다.
	{
		int moveFrontIndex = 0;
		for (int i = 0; i < DIRECTION - 2; i++)
		{
			int nnx = nx + diagonalX[moveFrontIndex]; // 앞으로 한칸 이동 했을 때 x
			int nny = ny + diagonalY[moveFrontIndex]; // 앞으로 한칸 이동 했을 때 y
			curPos = Board_index(nnx, nny);

			if (nnx < X_SIZE && nny < Y_SIZE && nnx >= 0 && nny >= 0 &&
				curPos >= 0 && curPos < BOARD_SIZE) // curPos가 배열을 초과하지 않으면 이동이 가능하다.
			{
				nnx += diagonalX[moveFrontIndex]; // 앞으로 두 칸 이동 했을 때 x
				nny += diagonalY[moveFrontIndex]; // 앞으로 두 칸 이동 했을 때 y
				curPos = Board_index(nnx, nny);

				if (nnx < X_SIZE && nny < Y_SIZE && nnx >= 0 && nny >= 0 &&
					curPos >= 0 && curPos < BOARD_SIZE &&
					boardIndexArr[curPos] >= EmptyHere) // curPos가 배열을 초과하지 않고 다음 이동할 위치가 비어있으면 이동이 가능하다.
				{
					bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);
					if (bisMove)possibleMove.Add(curPos);
				}
			}
			moveFrontIndex = 3;
		}
	}

	for (int i = 0; i < DIRECTION - 1; i++) // 왼쪽, 아래, 오른쪽 이동했을 경우만 고려
	{
		nx = xIndex + straightX[i + 1];
		ny = yIndex + straightY[i + 1];
		curPos = Board_index(nx, ny);

		for (int j = i; j < (i + 2); j++) // 정방향 이동할 경우 제외하고 이동한 좌표 2개 대각선만 탐색  straightX[i]가 -1이면 diagonalX는 -1이여야 한다.
		{
			// 한 칸 이동했을 때 길이 막혀있지 않고 비어 있어야 한다.
			if (nx < X_SIZE && ny < Y_SIZE && nx >= 0 && ny >= 0 &&
				curPos >= 0 && curPos < BOARD_SIZE) // curPos가 배열을 초과하지 않으면 이동이 가능하다.
			{
				int nnx = nx + diagonalX[j]; // 한 칸 이동 했을 때 x
				int nny = ny + diagonalY[j]; // 한 칸 이동 했을 때 y
				curPos = Board_index(nnx, nny);
				if (nnx < X_SIZE && nny < Y_SIZE && nnx >= 0 && nny >= 0 &&
					curPos >= 0 && curPos < BOARD_SIZE) // curPos가 배열을 초과하지 않으면 이동이 가능하다.
				{
					nnx += diagonalX[j]; // 두 칸 이동 했을 때 x
					nny += diagonalY[j]; // 두 칸 이동 했을 때 y
					curPos = Board_index(nnx, nny);

					if (nnx < X_SIZE && nny < Y_SIZE && nnx >= 0 && nny >= 0 &&
						curPos >= 0 && curPos < BOARD_SIZE &&
						boardIndexArr[curPos] >= EmptyHere) // curPos가 배열을 초과하지 않고 다음 이동할 위치가 비어있으면 이동이 가능하다.
					{
						bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);
						if (bisMove)possibleMove.Add(curPos);
					}
				}
			}
			curPos = Board_index(nx, ny); // 다시 한칸 앞으로 이동한 위치로 되돌려 준다.
		}
	}
	return possibleMove;
}

bool PiecesSkill::IsMove(const TArray<int32>& boardIndexArr, int32 xIndex, int32 yIndex, int32 curPos)
{
	bool bmove = false;
	if (curPos >= 0 && curPos < BOARD_SIZE && // 맵 바깥으로 나가지 말아야 하고
		(boardIndexArr[curPos] == EmptyHere || // 이동할 곳이 비어있거나
			(boardIndexArr[Board_index(xIndex, yIndex)] > RED_TEAM && boardIndexArr[curPos] <= RED_TEAM) || // 현재 눌린 돌이 초나라고 갈 수 있는 위치에 한나라가 없어야 함
			(boardIndexArr[Board_index(xIndex, yIndex)] <= RED_TEAM && boardIndexArr[curPos] > RED_TEAM)))  // 현재 눌린 돌이 한나라고 이동할 위치에 초나라가 있다면
	{
		bmove = true;
	}
	return bmove;
}

bool PiecesSkill::CheckEnemy(const TArray<int32>& boardIndexArr, int32 xIndex, int32 yIndex, int32 curPos)
{
	bool bmove = false;
	if (curPos < 0 || curPos >= BOARD_SIZE) {} // 맵 바깥으로 나가지 말아야 한다.	
	else if (
		boardIndexArr[curPos] != EmptyHere && // 비어 있지 않고
		(boardIndexArr[Board_index(xIndex, yIndex)] > RED_TEAM && boardIndexArr[curPos] <= RED_TEAM) || // 현재 눌린 돌이 초나라고 이동할 위치에 한나라가 있다면
		(boardIndexArr[Board_index(xIndex, yIndex)] <= RED_TEAM && boardIndexArr[curPos] > RED_TEAM))  // 현재 눌린 돌이 한나라고 이동할 위치에 초나라가 있다면
	{
		bmove = true;
	}
	return bmove;
}
