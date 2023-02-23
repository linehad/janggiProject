// Fill out your copyright notice in the Description page of Project Settings.


#include "Board.h"
#include "SoundManager.h"
#include "Explosion.h"
#include "JanggiFunction.h"
#include "JanggiGameStateBase.h"
#include "JanggiPlayerController.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
// Sets default values

ABoard::ABoard()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	pieciesMesh.Empty();
	fillPieciesMesh.Empty();
	fliedsMesh.Empty();
	explosionArr.Empty();
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

void ABoard::BP_JanggiDestroyComponent(int32 DestroyPos)
{
	{
		if (pieciesMesh[DestroyPos] == nullptr) return;
		else if (!bIsDestroy) return;
		JanggiDestroy(DestroyPos);
	}
}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AJanggiGameStateBase::StaticClass(), OutActors);
	for (AActor* a : OutActors)
	{
		JanggiState = Cast<AJanggiGameStateBase>(a);
	}
	JanggiController = Cast<AJanggiPlayerController>(GetWorld()->GetFirstPlayerController());
	OutActors.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASoundManager::StaticClass(), OutActors);
	for (AActor* a : OutActors)
	{
		SoundManager = Cast<ASoundManager>(a);
	}
}


void ABoard::SetMouseOver()
{
	for (int i = 0; i < pieciesMesh.Num(); i++)
	{
		if (JanggiState->GetBoardIndexArr()[i] == 0)
		{
			pieciesMesh[i]->DestroyComponent();
			fillPieciesMesh[i]->DestroyComponent();
			pieciesMesh[i] = nullptr;
			fillPieciesMesh[i] = nullptr;
		}
		else if (pieciesMesh[i] != nullptr)
		{
			pieciesMesh[i]->OnBeginCursorOver.AddDynamic(this, &ABoard::ShowPowerHealthMouseOver);
			pieciesMesh[i]->OnEndCursorOver.AddDynamic(this, &ABoard::EndMouseOver);
			fillPieciesMesh[i]->OnBeginCursorOver.AddDynamic(this, &ABoard::ShowPowerHealthMouseOver);
			fillPieciesMesh[i]->OnEndCursorOver.AddDynamic(this, &ABoard::EndMouseOver);
		}
	}
}

void ABoard::ShowPowerHealthMouseOver(UPrimitiveComponent* TouchedComponent)
{
	for (int i = 0; i < pieciesMesh.Num(); i++)
	{
		if (pieciesMesh[i] == TouchedComponent) {
			showHealthPos = i;
			break;
		}
	}
	int32 pieciesIndex = JanggiState->GetBoardIndexArr()[showHealthPos];
	JanggiController->ShowPowerHealth(GetPiecies(pieciesIndex), GetPower(pieciesIndex), JanggiState->GetHealthATKArr()[showHealthPos]);
}

void ABoard::EndMouseOver(UPrimitiveComponent* TouchedComponent)
{
	JanggiController->ShowPowerHealth(0, 0, 0);
}

// 내 앞에 있는 다른 말을 파괴한다. 이후 내 말을 움직임
void ABoard::JanggiDestroy(int32 DestroyPos)
{
	explosionArr[DestroyPos]->BP_Explosion();
	pieciesMesh[DestroyPos]->DestroyComponent();
	fillPieciesMesh[DestroyPos]->DestroyComponent();
}

void ABoard::ChkeckMove()
{
	const int BOARD_SIZE = 90;
	usingSkill = false;

	if (JanggiState->GetSkillUsing()) // 스킬 버튼을 눌렀다면
	{
		moveIndex = CheckSkillMove(JanggiState->GetBoardIndexArr(), curPosition, JanggiState->GetGameTurn());

		if (JanggiState->GetGameTurn() == Red && HasAuthority())
		{
			usingSkill = true;
		}
		else if (JanggiState->GetGameTurn() == Blue && !HasAuthority())
		{
			usingSkill = true;
		}
		if (HasAuthority()) // 서버 일 때만 바꿉니다.
		{
			JanggiController->SetSkillUsing(false);
		}
	}
	else
	{
		moveIndex = CheckMove(JanggiState->GetBoardIndexArr(), curPosition, JanggiState->GetGameTurn());
	}
	if (curPosition < 0 && curPosition >= BOARD_SIZE) return; // 잘못 된 값을 읽어 올 경우 아무것도 안함
	else if (JanggiState->GetLastTurn() == JanggiState->GetGameTurn()) return;// 이전에 착수한 사람과 게임턴이 같다면 아무것도 안함
	else if (moveIndex.Num() == 0) return;// 이동 할 곳이 없다면 아무것도 안함
	else if (JanggiState->GetBoardIndexArr()[curPosition] == Empty) return; // 비어있는 곳을 클릭할 경우 아무것도 안함

	SoundManager->PlaySound(SelectPieciesSoundEffect, SoundEffectVol);
	for (int i = 0; i < moveIndex.Num(); i++)
	{
		int possibleMove = moveIndex[i];
		fliedsMesh[possibleMove]->SetMaterial(0, fieldGoldsMaterial);

		FVector position = IndexToPosition(possibleMove) + FVector(50.5, 55.0, 9.0);;
		fliedsMesh[possibleMove]->SetWorldLocation(position); // 가야 하는곳 들어 올리기
	}

	fliedsMesh[curPosition]->SetMaterial(0, fieldWoodsMaterial); // 누른곳 색 변경

	FVector position = IndexToPosition(curPosition) + FVector(50.5, 55.0, 9.0);;
	fliedsMesh[curPosition]->SetWorldLocation(position); // 누른곳 들어 올리기
	fliedsMesh[curPosition]->SetRelativeScale3D(FVector(0.5, 0.5, 0.3)); // 누른곳 크게

	lastClick = curPosition;
}

void ABoard::IsMove()
{ 
	bool bisMove = false;
	for (int i = 0; i < moveIndex.Num(); i++)
	{
		if (curPosition == moveIndex[i]) // 비어있는 곳을 누른게 아닌지 판별
		{
			bisMove = true;
			break;
		}
	}
	for (int i = 0; i < moveIndex.Num(); i++)
	{
		int possibleMove = moveIndex[i];
		FVector position = IndexToPosition(possibleMove) + FVector(50.5, 55.0, 0);
		fliedsMesh[possibleMove]->SetWorldLocation(position); // 가야하는 곳 필드메시 낮추기
	}

	FVector position = IndexToPosition(lastClick) + FVector(50.5, 55.0, 0);
	fliedsMesh[lastClick]->SetWorldLocation(position); // 누른곳 필드메시 낮추기
	fliedsMesh[lastClick]->SetRelativeScale3D(FVector(0.4, 0.4, 0.3)); // 누른곳 작게

	if (JanggiState->GetGameTurn() == Red && 
		JanggiState->GetBoardIndexArr()[curPosition] != Empty && JanggiState->GetBoardIndexArr()[curPosition] <= RedPawn &&
		(curPosition != lastClick)) // 한나라이고 같은 곳을 누른게 아닐 때
	{
		ChkeckMove();
		return;
	}	
	else if (JanggiState->GetGameTurn() == Blue && 
		JanggiState->GetBoardIndexArr()[curPosition] > RedPawn && (curPosition != lastClick))// 초나라이고 같은 곳을 누른게 아닐 때
	{
		ChkeckMove();
		return;
	}
	else if (!bisMove) // 비어 있는 곳을 눌렀을 때
	{
		lastClick = -1; // 클릭을 초기화 한다.
		return;
	}
	else if (usingSkill) // 스킬 버튼이 눌렸을 때
	{
		skillCount--;
		JanggiController->UsingSkill(skillCount);
	}

	if (HasAuthority())
	{
		JanggiController->SetLastTurn(); // 서버 일때만 턴 변경 변경 후 클라로 뿌려줌
	}

	bIsDestroy = JanggiState->AttackPiecies(curPosition, lastClick);
	BP_JanggiDestroyComponent(curPosition); // 이동 할 수 있는 위치 일 때만 파괴한다.
	SetMovePiecies(); // 파괴한 말 위치로 이동한다.
	if (HasAuthority())
	{
		JanggiController->SetGameTurn(); // 서버 일때만 턴 변경 변경 후 클라로 뿌려줌
	}
	lastClick = -1; // 클릭을 초기화 한다.

	JanggiController->CountTurn(gameTurn); // 턴을 증가 시킨다.
	gameTurn = !gameTurn;

	if (JanggiState->Resurrection())
	{
		BP_ResurrectionEvent();
	}
}

void ABoard::ReStart()
{
	JanggiState->ResetArr();
	for (int i = 0; i < pieciesMesh.Num(); i++)
	{
		if (pieciesMesh[i] != nullptr)
		{
			pieciesMesh[i]->DestroyComponent();
		}
		if (fillPieciesMesh[i] != nullptr)
		{
			fillPieciesMesh[i]->DestroyComponent();
		}
	}
	if (HasAuthority())
	{
		JanggiState->SetGameTurn(2);
		JanggiState->SetlastTurn(1);
	}
	pieciesMesh.Empty();
	fillPieciesMesh.Empty();
	fliedsMesh.Empty();
	skillCount = 3;
}

void ABoard::SetMovePiecies()
{
	if (JanggiState->GetIsAttack())
	{
		explosionArr[curPosition]->BP_Attack();
	}
	if (!bIsDestroy) return; // 파괴하지 못했다면 움직이지 않는다.

	SoundManager->PlaySound(PutPieciesSoundEffect, SoundEffectVol);
	FVector position = IndexToPosition(curPosition) + FVector(50.5, 55.0, 10.0);
	pieciesMesh[lastClick]->SetWorldLocation(position); // 파괴된 말 위치로 이동

	position = IndexToPosition(curPosition) + FVector(50.5, 55.0, 18.0);
	fillPieciesMesh[lastClick]->SetWorldLocation(position); // 파괴된 말 위치로 이동

	JanggiState->MoveArr(curPosition, lastClick);

	pieciesMesh[curPosition] = pieciesMesh[lastClick];
	pieciesMesh[lastClick] = nullptr;

	fillPieciesMesh[curPosition] = fillPieciesMesh[lastClick];
	fillPieciesMesh[lastClick] = nullptr;
}