// Fill out your copyright notice in the Description page of Project Settings.


#include "JanggiPieces.h"

TArray<int32> JanggiPieces::Rook(int32 xIndex, int32 yIndex, const TArray<int32>& boardIndexArr, int32 PalaceYCenter, int32 PalaceStartingPoint, int32 PalaceEndPoint)
{
	// �����¿�� �������� �̵� �����Ѱ� üũ
// ���߿� �ÿ� ���� �밢�� �̵� ���� �ؾ���
	TArray<int32> possibleMove;
	possibleMove.Empty();

	for (int i = 0; i < DIRECTION; i++)
	{
		int nx = xIndex;
		int ny = yIndex;
		int curPos = Board_index(nx, ny);
		bool bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);

		// �밢�� Ž��
		if (curPos >= 0 && curPos < BOARD_SIZE && // �� �ٱ����� ������ ���ƾ� �ϰ�
			(((xIndex == PALACE_X_STARTING__POINT || xIndex == PALACE_X_END__POINT) && (yIndex == PalaceStartingPoint || yIndex == PalaceEndPoint))) ||
			(xIndex == 4 && yIndex == PalaceYCenter)) // ���� ��� �Ǵ� �������̿��� ��)
		{
			nx = xIndex + diagonalX[i];
			ny = yIndex + diagonalY[i];
			curPos = Board_index(nx, ny);
			bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);
			// �밢�� Ž��
			while (nx < X_SIZE && ny < Y_SIZE && nx >= 0 && ny >= 0 && curPos >= 0 && curPos < BOARD_SIZE && // �� �ٱ����� ������ ���ƾ� �ϰ�
				nx >= PALACE_X_STARTING__POINT && nx <= PALACE_X_END__POINT && ny >= PalaceStartingPoint && ny <= PalaceEndPoint && // �� ���� �����̿��� �ϸ�
				bisMove) // �̵��� ���� ���̰ų� ����־�� ��
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
			bisMove) // curPos�� �迭�� �ʰ����� �ʰ� ���� �̵��� ��ġ�� ��������� �̵��� �����ϴ�.
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

	// ������ �̵� �����Ѱ� üũ
	int nx = xIndex + straightX[0];
	int ny = yIndex + straightY[0];
	int curPos = Board_index(nx, ny);
	bool bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);
	// ������ ��ĭ �̵����� �� ��� �ִٸ�
	if (nx < X_SIZE && ny < Y_SIZE && nx >= 0 && ny >= 0 &&
		curPos >= 0 && curPos < BOARD_SIZE &&
		boardIndexArr[curPos] == EmptyHere) // curPos�� �迭�� �ʰ����� �ʰ� ���� �̵��� ��ġ�� ��������� �̵��� �����ϴ�.
	{
		int moveFrontIndex = 0;
		for (int i = 0; i < DIRECTION - 2; i++)
		{
			int nnx = nx + diagonalX[moveFrontIndex]; // ������ ��ĭ �̵� ���� �� x
			int nny = ny + diagonalY[moveFrontIndex]; // ������ ��ĭ �̵� ���� �� y
			curPos = Board_index(nnx, nny);

			if (nnx < X_SIZE && nny < Y_SIZE && nnx >= 0 && nny >= 0 &&
				curPos >= 0 && curPos < BOARD_SIZE &&
				boardIndexArr[curPos] >= EmptyHere) // curPos�� �迭�� �ʰ����� �ʰ� ���� �̵��� ��ġ�� ��������� �̵��� �����ϴ�.
			{
				bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);
				if (bisMove)possibleMove.Add(curPos);
			}
			moveFrontIndex = 3;
		}
	}

	for (int i = 0; i < DIRECTION - 1; i++) // ����, �Ʒ�, ������ �̵����� ��츸 ���
	{
		nx = xIndex + straightX[i + 1];
		ny = yIndex + straightY[i + 1];
		curPos = Board_index(nx, ny);

		for (int j = i; j < (i + 2); j++) // ������ �̵��� ��� �����ϰ� �̵��� ��ǥ 2�� �밢���� Ž��  straightX[i]�� -1�̸� diagonalX�� -1�̿��� �Ѵ�.
		{
			// ��ĭ �̵����� �� ��� �ִٸ�
			if (nx < X_SIZE && ny < Y_SIZE && nx >= 0 && ny >= 0 &&
				curPos >= 0 && curPos < BOARD_SIZE &&
				boardIndexArr[curPos] == EmptyHere) // curPos�� �迭�� �ʰ����� �ʰ� ���� �̵��� ��ġ�� ��������� �̵��� �����ϴ�.
			{
				int nnx = nx + diagonalX[j]; // ��ĭ �̵� ���� �� x
				int nny = ny + diagonalY[j]; // ��ĭ �̵� ���� �� y
				curPos = Board_index(nnx, nny);
				if (nnx < X_SIZE && nny < Y_SIZE && nnx >= 0 && nny >= 0 &&
					curPos >= 0 && curPos < BOARD_SIZE &&
					boardIndexArr[curPos] >= EmptyHere) // curPos�� �迭�� �ʰ����� �ʰ� ���� �̵��� ��ġ�� ��������� �̵��� �����ϴ�.
				{
					bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);
					if (bisMove)possibleMove.Add(curPos);
				}
			}
			curPos = Board_index(nx, ny); // �ٽ� ��ĭ ������ �̵��� ��ġ�� �ǵ��� �ش�.
		}
	}
	return possibleMove;
}

TArray<int32> JanggiPieces::Elephant(int32 xIndex, int32 yIndex, const TArray<int32>& boardIndexArr)
{
	TArray<int32> possibleMove;
	possibleMove.Empty();

	// ������ �̵� �����Ѱ� üũ
	int nx = xIndex + straightX[0];
	int ny = yIndex + straightY[0];
	int curPos = Board_index(nx, ny);
	bool bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);

	// ������ ��ĭ �̵����� �� ��� �ִٸ�
	if (nx < X_SIZE && ny < Y_SIZE && nx >= 0 && ny >= 0 &&
		curPos >= 0 && curPos < BOARD_SIZE &&
		boardIndexArr[curPos] == EmptyHere) // curPos�� �迭�� �ʰ����� �ʰ� ���� �̵��� ��ġ�� ��������� �̵��� �����ϴ�.
	{
		int moveFrontIndex = 0;
		for (int i = 0; i < DIRECTION - 2; i++)
		{
			int nnx = nx + diagonalX[moveFrontIndex]; // ������ ��ĭ �̵� ���� �� x
			int nny = ny + diagonalY[moveFrontIndex]; // ������ ��ĭ �̵� ���� �� y
			curPos = Board_index(nnx, nny);

			if (nnx < X_SIZE && nny < Y_SIZE && nnx >= 0 && nny >= 0 &&
				curPos >= 0 && curPos < BOARD_SIZE &&
				boardIndexArr[curPos] == EmptyHere) // curPos�� �迭�� �ʰ����� �ʰ� ���� �̵��� ��ġ�� ��������� �̵��� �����ϴ�.
			{
				nnx += diagonalX[moveFrontIndex]; // ������ �� ĭ �̵� ���� �� x
				nny += diagonalY[moveFrontIndex]; // ������ �� ĭ �̵� ���� �� y
				curPos = Board_index(nnx, nny);

				if (nnx < X_SIZE && nny < Y_SIZE && nnx >= 0 && nny >= 0 &&
					curPos >= 0 && curPos < BOARD_SIZE &&
					boardIndexArr[curPos] >= EmptyHere) // curPos�� �迭�� �ʰ����� �ʰ� ���� �̵��� ��ġ�� ��������� �̵��� �����ϴ�.
				{
					bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);
					if (bisMove)possibleMove.Add(curPos);
				}
			}
			moveFrontIndex = 3;
		}
	}

	for (int i = 0; i < DIRECTION - 1; i++) // ����, �Ʒ�, ������ �̵����� ��츸 ���
	{
		nx = xIndex + straightX[i + 1];
		ny = yIndex + straightY[i + 1];
		curPos = Board_index(nx, ny);

		for (int j = i; j < (i + 2); j++) // ������ �̵��� ��� �����ϰ� �̵��� ��ǥ 2�� �밢���� Ž��  straightX[i]�� -1�̸� diagonalX�� -1�̿��� �Ѵ�.
		{
			// �� ĭ �̵����� �� ���� �������� �ʰ� ��� �־�� �Ѵ�.
			if (nx < X_SIZE && ny < Y_SIZE && nx >= 0 && ny >= 0 &&
				curPos >= 0 && curPos < BOARD_SIZE &&
				boardIndexArr[curPos] == EmptyHere) // curPos�� �迭�� �ʰ����� �ʰ� ���� �̵��� ��ġ�� ��������� �̵��� �����ϴ�.
			{
				int nnx = nx + diagonalX[j]; // �� ĭ �̵� ���� �� x
				int nny = ny + diagonalY[j]; // �� ĭ �̵� ���� �� y
				curPos = Board_index(nnx, nny);
				if (nnx < X_SIZE && nny < Y_SIZE && nnx >= 0 && nny >= 0 &&
					curPos >= 0 && curPos < BOARD_SIZE &&
					boardIndexArr[curPos] == EmptyHere) // curPos�� �迭�� �ʰ����� �ʰ� ���� �̵��� ��ġ�� ��������� �̵��� �����ϴ�.
				{
					nnx += diagonalX[j]; // �� ĭ �̵� ���� �� x
					nny += diagonalY[j]; // �� ĭ �̵� ���� �� y
					curPos = Board_index(nnx, nny);

					if (nnx < X_SIZE && nny < Y_SIZE && nnx >= 0 && nny >= 0 &&
						curPos >= 0 && curPos < BOARD_SIZE &&
						boardIndexArr[curPos] >= EmptyHere) // curPos�� �迭�� �ʰ����� �ʰ� ���� �̵��� ��ġ�� ��������� �̵��� �����ϴ�.
					{
						bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);
						if (bisMove)possibleMove.Add(curPos);
					}
				}
			}
			curPos = Board_index(nx, ny); // �ٽ� ��ĭ ������ �̵��� ��ġ�� �ǵ��� �ش�.
		}
	}
	return possibleMove;
}

TArray<int32> JanggiPieces::GuardsAndKing(int32 xIndex, int32 yIndex, const TArray<int32>& boardIndexArr, int32 PalaceYCenter, int32 PalaceStartingPoint, int32 PalaceEndPoint)
{
	const int PALACE_CENTER = 4;

	TArray<int32> possibleMove;
	possibleMove.Empty();

	// ������ �̵� �����Ѱ� üũ
	int nx = xIndex;
	int ny = yIndex;
	int curPos = Board_index(nx, ny);
	bool bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);
	if ((nx == PALACE_CENTER && ny != PalaceYCenter) || ((nx != PALACE_CENTER && ny == PalaceYCenter))) // ����� �ƴϰ� �����¿쿡 ��ġ�� ������ �밢�� �̵��� �� �� ����.
	{
		for (int i = 0; i < DIRECTION; i++)
		{
			// �����¿� Ž��
			nx = xIndex + straightX[i];
			ny = yIndex + straightY[i];
			curPos = Board_index(nx, ny);
			bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);
			if (nx < X_SIZE && ny < Y_SIZE && nx >= 0 && ny >= 0 && curPos >= 0 && curPos < BOARD_SIZE && // �� �ٱ����� ������ ���ƾ� �ϰ�
				nx >= PALACE_X_STARTING__POINT && nx <= PALACE_X_END__POINT && ny >= PalaceStartingPoint && ny <= PalaceEndPoint && // �� ���� �����̿��� �ϸ�
				bisMove) // �̵��� ���� ����־�� �Ѵ�.
			{
				possibleMove.Add(curPos);
			}
		}
	}
	else
	{
		for (int i = 0; i < DIRECTION; i++)
		{
			// �����Ͽ� Ž��
			nx = xIndex + straightX[i];
			ny = yIndex + straightY[i];
			curPos = Board_index(nx, ny);
			bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);
			if (nx < X_SIZE && ny < Y_SIZE && nx >= 0 && ny >= 0 && curPos >= 0 && curPos < BOARD_SIZE && // �� �ٱ����� ������ ���ƾ� �ϰ�
				nx >= PALACE_X_STARTING__POINT && nx <= PALACE_X_END__POINT && ny >= PalaceStartingPoint && ny <= PalaceEndPoint && // �� ���� �����̿��� �ϸ�
				bisMove) // �̵��� ���� ����־�� �Ѵ�.
			{
				possibleMove.Add(curPos);
			}

			nx = xIndex + diagonalX[i];
			ny = yIndex + diagonalY[i];
			curPos = Board_index(nx, ny);
			bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);
			// �밢�� Ž��
			if (curPos >= 0 && curPos < BOARD_SIZE && // �� �ٱ����� ������ ���ƾ� �ϰ�
				nx >= PALACE_X_STARTING__POINT && nx <= PALACE_X_END__POINT && ny >= PalaceStartingPoint && ny <= PalaceEndPoint && // �� ���� �����̿��� �ϸ�
				bisMove) // �̵��� ���� ����־�� �Ѵ�.
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
	// �����¿�� �������� �̵� �����Ѱ� üũ
		// ���߿� �ÿ� ���� �밢�� �̵� ���� �ؾ���
	for (int i = 0; i < DIRECTION; i++)
	{
		bool bisCannon = false;
		bool bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);
		// �밢�� Ž��
		if (curPos >= 0 && curPos < BOARD_SIZE && // �� �ٱ����� ������ ���ƾ� �ϰ�
			(((xIndex == PALACE_X_STARTING__POINT || xIndex == PALACE_X_END__POINT) && (yIndex == PalaceStartingPoint || yIndex == PalaceEndPoint))) && // �������̿��� �ϸ�
			boardIndexArr[Board_index(4, PalaceYCenter)] != EmptyHere && // �� ��� ���� �־�� �ϸ�,
			boardIndexArr[Board_index(4, PalaceYCenter)]!= BlueCannon && boardIndexArr[Board_index(4, PalaceYCenter)] != RedCannon) // �� ���� �������� �ȵȴ�.
		{
			nx = xIndex + diagonalX[i];
			ny = yIndex + diagonalY[i];
			curPos = Board_index(nx, ny);

			if (nx < X_SIZE && ny < Y_SIZE && nx >= 0 && ny >= 0 && curPos >= 0 && curPos < BOARD_SIZE && // �迭�� �ʰ����� �ʰ�
				nx >= PALACE_X_STARTING__POINT && nx <= PALACE_X_END__POINT && ny >= PalaceStartingPoint && ny <= PalaceEndPoint && // �� ���� ������ ��
				boardIndexArr[curPos] != BlueCannon && boardIndexArr[curPos] != RedCannon && // ���� �ƴϰ�
				boardIndexArr[curPos] > EmptyHere) // �ٸ� ���� ������ ��
			{
				nx += diagonalX[i];
				ny += diagonalY[i];
				curPos = Board_index(nx, ny);
				bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);// ��� �ְų� ��� �� �̸� true
				if(bisMove)	possibleMove.Add(curPos);
			}
		}

		nx = xIndex + straightX[i];
		ny = yIndex + straightY[i];
		curPos = Board_index(nx, ny);

		while (nx < X_SIZE && ny < Y_SIZE && nx >= 0 && ny >= 0 &&
			curPos >= 0 && curPos < BOARD_SIZE) // curPos�� �迭�� �ʰ����� ������ �̵��� �����ϴ�.
		{
			if ((boardIndexArr[curPos] == BlueCannon || boardIndexArr[curPos] == RedCannon)) // �̵��ϸ鼭 ������ �����
			{
				bisCannon = true;
				break;
			}
			else if (boardIndexArr[curPos] > EmptyHere) // �ٸ� ���� ������ ��
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

		while (!bisCannon && nx < X_SIZE && ny < Y_SIZE && nx >= 0 && ny >= 0 && // ���� ���� curPos�� �迭�� �ʰ����� ������
			boardIndexArr[curPos] != BlueCannon && boardIndexArr[curPos] != RedCannon && // ���� �ƴϰ�
			bisMove) // �̵��� ���� ����� ���̰ų� ����־�� �Ѵ�.
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

	// ���¿��� ���� Ž�� (���� ���� �迭)
	const int32 pawnX[4] = { 0, -1, 1, 0 };
	const int32 pawnY[4] = { 1, 0, 0, -1 };

	int nx = xIndex;
	int ny = yIndex;
	int curPos = Board_index(nx, ny);
	int dX = 0;
	int dY = 2;
	// �밢�� Ž��
	if (curPos >= 0 && curPos < BOARD_SIZE && // �� �ٱ����� ������ ���ƾ� �ϰ�
		(((xIndex == PALACE_X_STARTING__POINT || xIndex == PALACE_X_END__POINT) && (yIndex == PalaceStartingPoint || yIndex == PalaceEndPoint))) || // �� ��ġ�� �������̰ų�
		(xIndex == 4 && yIndex == PalaceYCenter)) // �� �߾ӿ� ��� ���� ���
	{
		// �»� ��� ���� ���� �밢 Ž��
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
			// �밢�� Ž��
			if (nx >= PALACE_X_STARTING__POINT && nx <= PALACE_X_END__POINT && ny >= PalaceStartingPoint && ny <= PalaceEndPoint &&  // �̵��� ���� �� ���� �����̰�
				bisMove) // �̵��� ���� ����� ���̰ų� ����־�� �Ѵ�.
			{
				possibleMove.Add(curPos);
			}
		}
	}

	// ���¿� Ȥ�� �¿��� Ž��
	for (int i = pawnStartDirection; i < pawnEndDirection; i++)
	{
		nx = xIndex + pawnX[i];
		ny = yIndex + pawnY[i];
		curPos = Board_index(nx, ny);
		bool bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);
		if (nx < X_SIZE && ny < Y_SIZE && nx >= 0 && ny >= 0 && bisMove) // �� �ٱ����� ������ ���ƾ� �ϰ� �̵��� ���� ����� ���̰ų� ����־�� �Ѵ�.
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
	if (curPos >= 0 && curPos < BOARD_SIZE && // �� �ٱ����� ������ ���ƾ� �ϰ�
		(boardIndexArr[curPos] == EmptyHere || // �̵��� ���� ����ְų�
		(boardIndexArr[Board_index(xIndex, yIndex)] > RED_TEAM && boardIndexArr[curPos] <= RED_TEAM) || // ���� ���� ���� �ʳ���� �� �� �ִ� ��ġ�� �ѳ��� ����� ��
		(boardIndexArr[Board_index(xIndex, yIndex)] <= RED_TEAM && boardIndexArr[curPos] > RED_TEAM)))  // ���� ���� ���� �ѳ���� �̵��� ��ġ�� �ʳ��� �ִٸ�
	{
		bmove = true;
	}
		return bmove;
}

bool JanggiPieces::CheckEnemy(const TArray<int32>& boardIndexArr, int32 xIndex, int32 yIndex, int32 curPos)
{
	bool bmove = false;
	if (curPos < 0 || curPos >= BOARD_SIZE) {} // �� �ٱ����� ������ ���ƾ� �Ѵ�.	
	else if(
		boardIndexArr[curPos] != EmptyHere && // ��� ���� �ʰ�
		(boardIndexArr[Board_index(xIndex, yIndex)] > RED_TEAM && boardIndexArr[curPos] <= RED_TEAM) || // ���� ���� ���� �ʳ���� �̵��� ��ġ�� �ѳ��� �ִٸ�
			(boardIndexArr[Board_index(xIndex, yIndex)] <= RED_TEAM && boardIndexArr[curPos] > RED_TEAM))  // ���� ���� ���� �ѳ���� �̵��� ��ġ�� �ʳ��� �ִٸ�
	{
		bmove = true;
	}
	return bmove;
}
