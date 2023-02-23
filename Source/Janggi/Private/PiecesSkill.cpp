// Fill out your copyright notice in the Description page of Project Settings.


#include "PiecesSkill.h"

PiecesSkill::PiecesSkill()
{
}



TArray<int32> PiecesSkill::Knight(int32 xIndex, int32 yIndex, const TArray<int32>& boardIndexArr, int32 PalaceYCenter, int32 PalaceStartingPoint, int32 PalaceEndPoint)
{
	// �����¿�� �������� �̵� �����Ѱ� üũ
// ���߿� �ÿ� ���� �밢�� �̵� ���� �ؾ���
	TArray<int32> possibleMove;
	possibleMove.Empty();

	for (int i = 0; i < DIRECTION; i++) // ��� ���� Ž��
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

		for (int j = 0; j < 2; j++)
		{
			if (nx < X_SIZE && ny < Y_SIZE && nx >= 0 && ny >= 0 &&
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
		// �����Ͽ� Ž��
		nx = xIndex + straightX[i];
		ny = yIndex + straightY[i];
		curPos = Board_index(nx, ny);
		bool bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);
		if (nx < X_SIZE && ny < Y_SIZE && nx >= 0 && ny >= 0 && curPos >= 0 && curPos < BOARD_SIZE && // �� �ٱ����� ������ ���ƾ� �ϰ�
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
			bisMove) // �̵��� ���� ����־�� �Ѵ�.
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

	// ������ �̵� �����Ѱ� üũ
	int nx = xIndex + straightX[0];
	int ny = yIndex + straightY[0];
	int curPos = Board_index(nx, ny);
	bool bisMove = IsMove(boardIndexArr, xIndex, yIndex, curPos);

	// ������ ��ĭ �̵����� �� ��� �ִٸ�
	if (nx < X_SIZE && ny < Y_SIZE && nx >= 0 && ny >= 0 &&
		curPos >= 0 && curPos < BOARD_SIZE) // curPos�� �迭�� �ʰ����� ������ �̵��� �����ϴ�.
	{
		int moveFrontIndex = 0;
		for (int i = 0; i < DIRECTION - 2; i++)
		{
			int nnx = nx + diagonalX[moveFrontIndex]; // ������ ��ĭ �̵� ���� �� x
			int nny = ny + diagonalY[moveFrontIndex]; // ������ ��ĭ �̵� ���� �� y
			curPos = Board_index(nnx, nny);

			if (nnx < X_SIZE && nny < Y_SIZE && nnx >= 0 && nny >= 0 &&
				curPos >= 0 && curPos < BOARD_SIZE) // curPos�� �迭�� �ʰ����� ������ �̵��� �����ϴ�.
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
				curPos >= 0 && curPos < BOARD_SIZE) // curPos�� �迭�� �ʰ����� ������ �̵��� �����ϴ�.
			{
				int nnx = nx + diagonalX[j]; // �� ĭ �̵� ���� �� x
				int nny = ny + diagonalY[j]; // �� ĭ �̵� ���� �� y
				curPos = Board_index(nnx, nny);
				if (nnx < X_SIZE && nny < Y_SIZE && nnx >= 0 && nny >= 0 &&
					curPos >= 0 && curPos < BOARD_SIZE) // curPos�� �迭�� �ʰ����� ������ �̵��� �����ϴ�.
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

bool PiecesSkill::IsMove(const TArray<int32>& boardIndexArr, int32 xIndex, int32 yIndex, int32 curPos)
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

bool PiecesSkill::CheckEnemy(const TArray<int32>& boardIndexArr, int32 xIndex, int32 yIndex, int32 curPos)
{
	bool bmove = false;
	if (curPos < 0 || curPos >= BOARD_SIZE) {} // �� �ٱ����� ������ ���ƾ� �Ѵ�.	
	else if (
		boardIndexArr[curPos] != EmptyHere && // ��� ���� �ʰ�
		(boardIndexArr[Board_index(xIndex, yIndex)] > RED_TEAM && boardIndexArr[curPos] <= RED_TEAM) || // ���� ���� ���� �ʳ���� �̵��� ��ġ�� �ѳ��� �ִٸ�
		(boardIndexArr[Board_index(xIndex, yIndex)] <= RED_TEAM && boardIndexArr[curPos] > RED_TEAM))  // ���� ���� ���� �ѳ���� �̵��� ��ġ�� �ʳ��� �ִٸ�
	{
		bmove = true;
	}
	return bmove;
}
