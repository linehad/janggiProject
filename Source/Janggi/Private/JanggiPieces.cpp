// Fill out your copyright notice in the Description page of Project Settings.


#include "JanggiPieces.h"

TArray<int32> JanggiPieces::Rook(int32 xIndex, int32 yIndex, const TArray<int32>& boardIndexArr, int32 PalaceYCenter, int32 PalaceStartingPoint, int32 PalaceEndPoint)
{
	// 상하좌우로 움직여서 이동 가능한곳 체크
// 나중에 궁에 들어가면 대각선 이동 구현 해야함
	TArray<int32> possibleMove;
	possibleMove.Empty();

	for (int i = 0; i < DIRECTION; i++)
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

		while (nx < X_SIZE && ny < Y_SIZE && nx >= 0 && ny >= 0 &&
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
	return possibleMove;
}

TArray<int32> JanggiPieces::Knight(int32 xIndex, int32 yIndex, const TArray<int32>& boardIndexArr)
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
		curPos >= 0 && curPos < BOARD_SIZE &&
		boardIndexArr[curPos] == EmptyHere) // curPos가 배열을 초과하지 않고 다음 이동할 위치가 비어있으면 이동이 가능하다.
	{
		int moveFrontIndex = 0;
		for (int i = 0; i < DIRECTION - 2; i++)
		{
			int nnx = nx + diagonalX[moveFrontIndex]; // 앞으로 한칸 이동 했을 때 x
			int nny = ny + diagonalY[moveFrontIndex]; // 앞으로 한칸 이동 했을 때 y
			curPos = Board_index(nnx, nny);

			if (nnx < X_SIZE && nny < Y_SIZE && nnx >= 0 && nny >= 0 &&
				curPos >= 0 && curPos < BOARD_SIZE &&
				boardIndexArr[curPos] >= EmptyHere) // curPos가 배열을 초과하지 않고 다음 이동할 위치가 비어있으면 이동이 가능하다.
			{
				bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);
				if (bisMove)possibleMove.Add(curPos);
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
			// 한칸 이동했을 때 비어 있다면
			if (nx < X_SIZE && ny < Y_SIZE && nx >= 0 && ny >= 0 &&
				curPos >= 0 && curPos < BOARD_SIZE &&
				boardIndexArr[curPos] == EmptyHere) // curPos가 배열을 초과하지 않고 다음 이동할 위치가 비어있으면 이동이 가능하다.
			{
				int nnx = nx + diagonalX[j]; // 한칸 이동 했을 때 x
				int nny = ny + diagonalY[j]; // 한칸 이동 했을 때 y
				curPos = Board_index(nnx, nny);
				if (nnx < X_SIZE && nny < Y_SIZE && nnx >= 0 && nny >= 0 &&
					curPos >= 0 && curPos < BOARD_SIZE &&
					boardIndexArr[curPos] >= EmptyHere) // curPos가 배열을 초과하지 않고 다음 이동할 위치가 비어있으면 이동이 가능하다.
				{
					bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);
					if (bisMove)possibleMove.Add(curPos);
				}
			}
			curPos = Board_index(nx, ny); // 다시 한칸 앞으로 이동한 위치로 되돌려 준다.
		}
	}
	return possibleMove;
}

TArray<int32> JanggiPieces::Elephant(int32 xIndex, int32 yIndex, const TArray<int32>& boardIndexArr)
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
		curPos >= 0 && curPos < BOARD_SIZE &&
		boardIndexArr[curPos] == EmptyHere) // curPos가 배열을 초과하지 않고 다음 이동할 위치가 비어있으면 이동이 가능하다.
	{
		int moveFrontIndex = 0;
		for (int i = 0; i < DIRECTION - 2; i++)
		{
			int nnx = nx + diagonalX[moveFrontIndex]; // 앞으로 한칸 이동 했을 때 x
			int nny = ny + diagonalY[moveFrontIndex]; // 앞으로 한칸 이동 했을 때 y
			curPos = Board_index(nnx, nny);

			if (nnx < X_SIZE && nny < Y_SIZE && nnx >= 0 && nny >= 0 &&
				curPos >= 0 && curPos < BOARD_SIZE &&
				boardIndexArr[curPos] == EmptyHere) // curPos가 배열을 초과하지 않고 다음 이동할 위치가 비어있으면 이동이 가능하다.
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
				curPos >= 0 && curPos < BOARD_SIZE &&
				boardIndexArr[curPos] == EmptyHere) // curPos가 배열을 초과하지 않고 다음 이동할 위치가 비어있으면 이동이 가능하다.
			{
				int nnx = nx + diagonalX[j]; // 한 칸 이동 했을 때 x
				int nny = ny + diagonalY[j]; // 한 칸 이동 했을 때 y
				curPos = Board_index(nnx, nny);
				if (nnx < X_SIZE && nny < Y_SIZE && nnx >= 0 && nny >= 0 &&
					curPos >= 0 && curPos < BOARD_SIZE &&
					boardIndexArr[curPos] == EmptyHere) // curPos가 배열을 초과하지 않고 다음 이동할 위치가 비어있으면 이동이 가능하다.
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

TArray<int32> JanggiPieces::GuardsAndKing(int32 xIndex, int32 yIndex, const TArray<int32>& boardIndexArr, int32 PalaceYCenter, int32 PalaceStartingPoint, int32 PalaceEndPoint)
{
	const int PALACE_CENTER = 4;

	TArray<int32> possibleMove;
	possibleMove.Empty();

	// 전진시 이동 가능한곳 체크
	int nx = xIndex;
	int ny = yIndex;
	int curPos = Board_index(nx, ny);
	bool bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);
	if ((nx == PALACE_CENTER && ny != PalaceYCenter) || ((nx != PALACE_CENTER && ny == PalaceYCenter))) // 가운데가 아니고 상하좌우에 위치해 있으면 대각선 이동을 할 수 없다.
	{
		for (int i = 0; i < DIRECTION; i++)
		{
			// 상하좌우 탐색
			nx = xIndex + straightX[i];
			ny = yIndex + straightY[i];
			curPos = Board_index(nx, ny);
			bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);
			if (nx < X_SIZE && ny < Y_SIZE && nx >= 0 && ny >= 0 && curPos >= 0 && curPos < BOARD_SIZE && // 맵 바깥으로 나가지 말아야 하고
				nx >= PALACE_X_STARTING__POINT && nx <= PALACE_X_END__POINT && ny >= PalaceStartingPoint && ny <= PalaceEndPoint && // 궁 범위 안쪽이여야 하며
				bisMove) // 이동할 곳이 비어있어야 한다.
			{
				possibleMove.Add(curPos);
			}
		}
	}
	else
	{
		for (int i = 0; i < DIRECTION; i++)
		{
			// 상좌하우 탐색
			nx = xIndex + straightX[i];
			ny = yIndex + straightY[i];
			curPos = Board_index(nx, ny);
			bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);
			if (nx < X_SIZE && ny < Y_SIZE && nx >= 0 && ny >= 0 && curPos >= 0 && curPos < BOARD_SIZE && // 맵 바깥으로 나가지 말아야 하고
				nx >= PALACE_X_STARTING__POINT && nx <= PALACE_X_END__POINT && ny >= PalaceStartingPoint && ny <= PalaceEndPoint && // 궁 범위 안쪽이여야 하며
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
				nx >= PALACE_X_STARTING__POINT && nx <= PALACE_X_END__POINT && ny >= PalaceStartingPoint && ny <= PalaceEndPoint && // 궁 범위 안쪽이여야 하며
				bisMove) // 이동할 곳이 비어있어야 한다.
			{
				possibleMove.Add(curPos);
			}
		}
	}
	return possibleMove;
}

TArray<int32> JanggiPieces::Cannon(int32 xIndex, int32 yIndex, const TArray<int32>& boardIndexArr, int32 PalaceYCenter, int32 PalaceStartingPoint, int32 PalaceEndPoint, int32 pos)
{
	TArray<int32> possibleMove;
	possibleMove.Empty();

	int nx = xIndex;
	int ny = yIndex;
	int curPos = Board_index(nx, ny);
	// 상하좌우로 움직여서 이동 가능한곳 체크
		// 나중에 궁에 들어가면 대각선 이동 구현 해야함
	for (int i = 0; i < DIRECTION; i++)
	{
		bool bisCannon = false;
		bool bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);
		// 대각선 탐색
		if (curPos >= 0 && curPos < BOARD_SIZE && // 맵 바깥으로 나가지 말아야 하고
			(((xIndex == PALACE_X_STARTING__POINT || xIndex == PALACE_X_END__POINT) && (yIndex == PalaceStartingPoint || yIndex == PalaceEndPoint))) && // 꼭짓점이여야 하며
			boardIndexArr[Board_index(4, PalaceYCenter)] != EmptyHere && // 궁 가운데 말이 있어야 하며,
			boardIndexArr[Board_index(4, PalaceYCenter)]!= BlueCannon && boardIndexArr[Board_index(4, PalaceYCenter)] != RedCannon) // 그 말은 포여서는 안된다.
		{
			nx = xIndex + diagonalX[i];
			ny = yIndex + diagonalY[i];
			curPos = Board_index(nx, ny);

			if (nx < X_SIZE && ny < Y_SIZE && nx >= 0 && ny >= 0 && curPos >= 0 && curPos < BOARD_SIZE && // 배열을 초과하지 않고
				nx >= PALACE_X_STARTING__POINT && nx <= PALACE_X_END__POINT && ny >= PalaceStartingPoint && ny <= PalaceEndPoint && // 궁 범위 안쪽일 때
				boardIndexArr[curPos] != BlueCannon && boardIndexArr[curPos] != RedCannon && // 포가 아니고
				boardIndexArr[curPos] > EmptyHere) // 다른 말을 만났을 때
			{
				nx += diagonalX[i];
				ny += diagonalY[i];
				curPos = Board_index(nx, ny);
				bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);// 비어 있거나 상대 말 이면 true
				if(bisMove)	possibleMove.Add(curPos);
			}
		}

		nx = xIndex + straightX[i];
		ny = yIndex + straightY[i];
		curPos = Board_index(nx, ny);

		while (nx < X_SIZE && ny < Y_SIZE && nx >= 0 && ny >= 0 &&
			curPos >= 0 && curPos < BOARD_SIZE) // curPos가 배열을 초과하지 않으면 이동이 가능하다.
		{
			if ((boardIndexArr[curPos] == BlueCannon || boardIndexArr[curPos] == RedCannon)) // 이동하면서 만난게 포라면
			{
				bisCannon = true;
				break;
			}
			else if (boardIndexArr[curPos] > EmptyHere) // 다른 말을 만났을 때
			{
				nx += straightX[i];
				ny += straightY[i];
				curPos = Board_index(nx, ny);
				bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);
				break;
			}
			nx += straightX[i];
			ny += straightY[i];
			curPos = Board_index(nx, ny);
		}

		while (!bisCannon && nx < X_SIZE && ny < Y_SIZE && nx >= 0 && ny >= 0 && // 포가 없고 curPos가 배열을 초과하지 않으며
			boardIndexArr[curPos] != BlueCannon && boardIndexArr[curPos] != RedCannon && // 포가 아니고
			bisMove) // 이동할 곳이 상대팀 말이거나 비어있어야 한다.
		{
			if (nx >= X_SIZE || ny >= Y_SIZE&& nx < 0 || ny < 0)break;
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
		curPos = Board_index(xIndex, yIndex);
	}
	return possibleMove;
}

TArray<int32> JanggiPieces::Pawn(int32 xIndex, int32 yIndex, const TArray<int32>& boardIndexArr, int32 pawnStartDirection, int32 pawnEndDirection, int32 PalaceYCenter, int32 PalaceStartingPoint, int32 PalaceEndPoint)
{
	TArray<int32> possibleMove;
	possibleMove.Empty();

	// 상좌우하 직선 탐색 (졸을 위한 배열)
	const int32 pawnX[4] = { 0, -1, 1, 0 };
	const int32 pawnY[4] = { 1, 0, 0, -1 };

	int nx = xIndex;
	int ny = yIndex;
	int curPos = Board_index(nx, ny);
	int dX = 0;
	int dY = 2;
	// 대각선 탐색
	if (curPos >= 0 && curPos < BOARD_SIZE && // 맵 바깥으로 나가지 말아야 하고
		(((xIndex == PALACE_X_STARTING__POINT || xIndex == PALACE_X_END__POINT) && (yIndex == PalaceStartingPoint || yIndex == PalaceEndPoint))) || // 현 위치가 꼭짓점이거나
		(xIndex == 4 && yIndex == PalaceYCenter)) // 궁 중앙에 들어 갔을 경우
	{
		// 좌상 우상 좌하 우하 대각 탐색
		int32 pawnDiagonalX[4] = { -1, 1, -1, 1 };
		int32 pawnDiagonalY[4] = { 1, 1, -1, -1 };
		if (pawnStartDirection > 0)
		{
			dX += 2;
			dY += 2;
		}
		for (int i = dX; i < dY; i++)
		{
			nx = xIndex + pawnDiagonalX[i];
			ny = yIndex + pawnDiagonalY[i];
			curPos = Board_index(nx, ny);
			bool bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);
			// 대각선 탐색
			if (nx >= PALACE_X_STARTING__POINT && nx <= PALACE_X_END__POINT && ny >= PalaceStartingPoint && ny <= PalaceEndPoint &&  // 이동할 곳이 궁 범위 안쪽이고
				bisMove) // 이동할 곳이 상대팀 말이거나 비어있어야 한다.
			{
				possibleMove.Add(curPos);
			}
		}
	}

	// 상좌우 혹은 좌우하 탐색
	for (int i = pawnStartDirection; i < pawnEndDirection; i++)
	{
		nx = xIndex + pawnX[i];
		ny = yIndex + pawnY[i];
		curPos = Board_index(nx, ny);
		bool bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);
		if (nx < X_SIZE && ny < Y_SIZE && nx >= 0 && ny >= 0 && bisMove) // 맵 바깥으로 나가지 말아야 하고 이동할 곳이 상대팀 말이거나 비어있어야 한다.
		{
			possibleMove.Add(curPos);
		}
		curPos = Board_index(xIndex, yIndex);
	}
	return possibleMove;
}

bool JanggiPieces::IsMove(const TArray<int32>& boardIndexArr, int32 xIndex, int32 yIndex, int32 curPos)
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

bool JanggiPieces::CheckEnemy(const TArray<int32>& boardIndexArr, int32 xIndex, int32 yIndex, int32 curPos)
{
	bool bmove = false;
	if (curPos < 0 || curPos >= BOARD_SIZE) {} // 맵 바깥으로 나가지 말아야 한다.	
	else if(
		boardIndexArr[curPos] != EmptyHere && // 비어 있지 않고
		(boardIndexArr[Board_index(xIndex, yIndex)] > RED_TEAM && boardIndexArr[curPos] <= RED_TEAM) || // 현재 눌린 돌이 초나라고 이동할 위치에 한나라가 있다면
			(boardIndexArr[Board_index(xIndex, yIndex)] <= RED_TEAM && boardIndexArr[curPos] > RED_TEAM))  // 현재 눌린 돌이 한나라고 이동할 위치에 초나라가 있다면
	{
		bmove = true;
	}
	return bmove;
}
