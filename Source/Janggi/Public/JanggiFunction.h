// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum Turn
{
	Empty = 0,
	Red,
	Blue
};

enum PieciesPower
{
	RookPower = 5,
	KnightPower = 7,
	ElephantPower = 11,
	CannonPower = 13,
	PawnPower = 13,
	GuardsPower = 14,
	KingPower = 14,
	PieciesHealth = 14
};

/**
 * 
 */

int32 Attack(TArray<int32>& healthATKArr, TArray<int32>& boardIndexArr, int32 curPosition, int32 lastClick);
int32 GetY(int32 pos);
int32 GetX(int32 y, int32 pos);
int32 GetPower(int32 Piecies);
int32 GetPiecies(int32 Piecies);
TArray<int32> CheckMove(const TArray<int32>& boardIndexArr, int32 pos, int32 turn); // 한나라 일 때 장기판과 눌린 포지션 값을 받아서 계산한다.
TArray<int32> CheckSkillMove(const TArray<int32>& boardIndexArr, int32 pos, int32 turn); // 한나라 일 때 장기판과 눌린 포지션 값을 받아서 계산한다.

inline int32 GetBoardIndex(int32 x, int32 y)
{
	const int32 XSize = 9;
	return (XSize * y) + x; // 2차원 배열처럼 쓰기위한 식
}