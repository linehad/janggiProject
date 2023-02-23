// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialJanggiBoard.h"
#include "TutorialController.h"
#include "JanggiFunction.h"

// Sets default values
ATutorialJanggiBoard::ATutorialJanggiBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UpDownIndex.Empty();
	static ConstructorHelpers::FObjectFinder<UMaterial> Floor(TEXT("Material'/Game/StarterContent/Materials/M_Basic_Floor.M_Basic_Floor'"));
	if (Floor.Succeeded())
	{
		fieldsMaterial = Floor.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> Stone(TEXT("Material'/Game/StarterContent/Materials/M_Brick_Cut_Stone.M_Brick_Cut_Stone'"));
	if (Stone.Succeeded())
	{
		fieldGoldsMaterial = Stone.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> Wood(TEXT("Material'/Game/StarterContent/Materials/M_Wood_Floor_Walnut_Polished.M_Wood_Floor_Walnut_Polished'"));
	if (Wood.Succeeded())
	{
		fieldWoodsMaterial = Wood.Object;
	}
}

// Called when the game starts or when spawned
void ATutorialJanggiBoard::BeginPlay()
{
	Super::BeginPlay();
	for (int i = 0; i < pieciesMesh.Num(); i++)
	{
		pieciesMesh[i]->OnBeginCursorOver.AddDynamic(this, &ATutorialJanggiBoard::ShowPowerHealthMouseOver);
		pieciesMesh[i]->OnEndCursorOver.AddDynamic(this, &ATutorialJanggiBoard::EndMouseOver);
		fillPieciesMesh[i]->OnBeginCursorOver.AddDynamic(this, &ATutorialJanggiBoard::ShowPowerHealthMouseOver);
		fillPieciesMesh[i]->OnEndCursorOver.AddDynamic(this, &ATutorialJanggiBoard::EndMouseOver);
	}
	JanggiController = Cast<ATutorialController>(GetWorld()->GetFirstPlayerController());
}

void ATutorialJanggiBoard::DownPiecies(int index)
{
	FVector position = IndexToPosition(index) + FVector(50.5, 55.0, 0);;
	pieciesMesh[index]->SetWorldLocation(position);
	position = IndexToPosition(index) + FVector(50.5, 55.0, 0);;
	fillPieciesMesh[index]->SetWorldLocation(position);
}

void ATutorialJanggiBoard::MovePiecies(int thisIndex, int moveIndex)
{
	FVector position = IndexToPosition(moveIndex) + FVector(50.5, 55.0, 10.0);
	pieciesMesh[thisIndex]->SetWorldLocation(position); // 파괴된 말 위치로 이동
	position = IndexToPosition(moveIndex) + FVector(50.5, 55.0, 18.0);
	fillPieciesMesh[thisIndex]->SetWorldLocation(position); // 파괴된 말 위치로 이동
}

void ATutorialJanggiBoard::ShowPowerHealthMouseOver(UPrimitiveComponent* TouchedComponent)
{
	const int redPawn = 58;
	for (int i = 0; i < pieciesMesh.Num(); i++)
	{
		if (pieciesMesh[i] == TouchedComponent) {
			Pos = i;
			break;
		}
	}
	if (tutorialFlow7 && (pieciesMesh[redPawn] == TouchedComponent || fillPieciesMesh[redPawn] == TouchedComponent))
	{
		healPos = 1;
	}
	else
	{
		healPos = 0;
	}

	int32 pieciesIndex = boardIndexArr[Pos];
	JanggiController->ShowPowerHealth(GetPiecies(pieciesIndex), GetPower(pieciesIndex), health[healPos]);
}

void ATutorialJanggiBoard::EndMouseOver(UPrimitiveComponent* TouchedComponent)
{
	JanggiController->ShowPowerHealth(0, 0, 0);
}

void ATutorialJanggiBoard::TutorialFlow(int32 index)
{
	const int knight = 51;
	const int redPawn = 58;
	const int pawn1 = 68;
	const int pawn2 = 67;
	const int guards = 66;
	const int king = 76;
	const int elephant = 50;
	switch (index)
	{
	case 2:
		DownPiecies(king);
		break;
	case 3:
		MovePiecies(king, redPawn);
		break;
	case 4:
		DownPiecies(king);
		for (int i = 46; i <= 53; i++)
		{
			DownPiecies(i);
		}
		break;
	case 5:
	case 6:
		tutorialFlow7 = false;
		DownPiecies(redPawn);
		for (int i = 46; i <= 53; i++)
		{
			MovePiecies(i, i);
		}
		break;
	case 7:
		tutorialFlow7 = true;
		for (int i = 46; i <= 53; i++)
		{
			DownPiecies(i);
		}
		MovePiecies(knight, knight);
		MovePiecies(redPawn, redPawn);
		break;
	case 8:
		tutorialFlow7 = false;
		DownPiecies(pawn1);
		DownPiecies(guards);
		MovePiecies(knight, redPawn);
		DownPiecies(redPawn);
		break;
	case 9:
		MovePiecies(knight, knight);
		DownPiecies(knight);
		MovePiecies(pawn1, pawn1);
		MovePiecies(guards, guards);
		break;
	case 10:
		MovePiecies(pawn1, pawn2);
		DownPiecies(guards);
		break;
	case 11:
		DownPiecies(guards);
		MovePiecies(pawn1, king);
		break;
	case 12:
	case 13:
		DownPiecies(king);
		DownPiecies(pawn2);
		DownPiecies(pawn1);
		MovePiecies(guards, pawn2);
		break;
	case 14:
		DownPiecies(guards);
		MovePiecies(pawn2, pawn2);
		MovePiecies(king, king);
		break;
	case 15:
		DownPiecies(redPawn);
		MovePiecies(pawn2, king);
		DownPiecies(king);
		break;
	case 16:
		DownPiecies(king);
		DownPiecies(pawn2);
		DownPiecies(knight);
		DownPiecies(elephant);
		DownPiecies(pawn1);
		MovePiecies(redPawn, king);
		break;
	case 17:
		DownPiecies(redPawn);
		MovePiecies(knight, redPawn + 1);
		MovePiecies(elephant, redPawn);
		MovePiecies(pawn1, redPawn - 1);
		break;
	case 19:
		MovePiecies(knight, redPawn + 1);
		MovePiecies(elephant, redPawn);
		MovePiecies(pawn1, redPawn - 1);
		DownBoard(UpDownIndex, pawn2);
		UpDownIndex.Empty();
		break;
	case 20:
		DownPiecies(elephant);
		DownPiecies(pawn1);
		DownBoard(UpDownIndex, king);
		UpDownIndex.Empty();
		UpDownIndex.Add(king);
		UpDownIndex.Add(85);
		UpDownIndex.Add(redPawn);
		UpDownIndex.Add(49);
		for (int i = pawn2 - 2; i <= pawn2 + 2; i++)
		{
			UpDownIndex.Add(i);
		}
		UpBoard(UpDownIndex, pawn2);

		MovePiecies(knight, pawn2);
		break;
	case 21:
		DownBoard(UpDownIndex, pawn2);
		UpDownIndex.Empty();
		UpDownIndex.Add(47);
		UpDownIndex.Add(knight);
		UpDownIndex.Add(55);
		UpDownIndex.Add(61);
		UpBoard(UpDownIndex, king);

		DownPiecies(knight);
		MovePiecies(pawn1, pawn2);
		MovePiecies(elephant, king);
		break;
	case 22:
		DownBoard(UpDownIndex, king);
		UpDownIndex.Empty();
		for (int i = 3; i > 0; i--)
		{
			int temp = pawn2 + 2;
			UpDownIndex.Add(temp - i);
			temp = king + 2;
			UpDownIndex.Add(temp - i);
			temp = 87;
			UpDownIndex.Add(temp - i);
		}
		UpBoard(UpDownIndex, king);
		DownPiecies(elephant);
		DownPiecies(pawn1);

		MovePiecies(pawn1, king);
		break;
	case 23:
		DownBoard(UpDownIndex, king);
		UpDownIndex.Empty();

		DownPiecies(pawn1);
		break;
	default:
		break;
	}
}

void ATutorialJanggiBoard::UpBoard(TArray<int32> moveIndex, int32 Position)
{
	for (int i = 0; i < moveIndex.Num(); i++)
	{
		int possibleMove = moveIndex[i];
		fliedsMesh[possibleMove]->SetMaterial(0, fieldGoldsMaterial);

		FVector position = IndexToPosition(possibleMove) + FVector(50.5, 55.0, 9.0);;
		fliedsMesh[possibleMove]->SetWorldLocation(position); // 가야 하는곳 들어 올리기
	}

	fliedsMesh[Position]->SetMaterial(0, fieldWoodsMaterial); // 누른곳 색 변경

	FVector position = IndexToPosition(Position) + FVector(50.5, 55.0, 9.0);;
	fliedsMesh[Position]->SetWorldLocation(position); // 누른곳 들어 올리기
	fliedsMesh[Position]->SetRelativeScale3D(FVector(0.5, 0.5, 0.3)); // 누른곳 크게
}
void ATutorialJanggiBoard::DownBoard(TArray<int32> moveIndex, int32 Position)
{
	for (int i = 0; i < moveIndex.Num(); i++)
	{
		int possibleMove = moveIndex[i];
		FVector position = IndexToPosition(possibleMove) + FVector(50.5, 55.0, 0);
		fliedsMesh[possibleMove]->SetWorldLocation(position); // 가야하는 곳 필드메시 낮추기
	}

	FVector position = IndexToPosition(Position) + FVector(50.5, 55.0, 0);
	fliedsMesh[Position]->SetWorldLocation(position); // 누른곳 필드메시 낮추기
	fliedsMesh[Position]->SetRelativeScale3D(FVector(0.4, 0.4, 0.3)); // 누른곳 작게
}
FVector IndexToPosition(int index) 
{ 
	return FVector((index / 9) * 101.0, (index % 9) * 110.0, 0.0);
}