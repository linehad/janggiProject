// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TutorialJanggiBoard.generated.h"

UCLASS()
class JANGGI_API ATutorialJanggiBoard : public AActor
{
	GENERATED_BODY()
private:
	class ATutorialController* JanggiController;
	int32 Pos = 0;
	int32 healPos = 0;
	bool tutorialFlow7 = false;
	TArray<int32> health = { 14,7 };
	TArray<int32> UpDownIndex;
	UMaterial* fieldGoldsMaterial = nullptr;
	UMaterial* fieldWoodsMaterial = nullptr;
protected:
	UPROPERTY(BlueprintReadWrite, Category = "BoardVal")
		TArray<UStaticMeshComponent*> fliedsMesh;
	UPROPERTY(BlueprintReadWrite, Category = "BoardVal")
		TArray<UStaticMeshComponent*> pieciesMesh;
	UPROPERTY(BlueprintReadWrite, Category = "BoardVal")
		TArray<UStaticMeshComponent*> fillPieciesMesh;

	UPROPERTY(BlueprintReadWrite, Category = "BoardVal")
		UMaterial* fieldsMaterial = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = "BoardVal")
		TArray<int32> boardIndexArr =
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 12, 11, 14, 13, 10, 9, 8, 0,
		0, 0, 0, 0, 7, 0, 0, 0, 0,
		0, 0, 0, 11, 14, 14, 0, 0, 0,
		0, 0, 0, 0, 12, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0 };
public:	
	// Sets default values for this actor's properties
	ATutorialJanggiBoard();
	UFUNCTION()
	void TutorialFlow(int32 index);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector IndexToPosition(int index) { return FVector((index / 9) * 101.0, (index % 9) * 110.0, 0.0); }
	int32 PositionToIndex(FVector position)
	{
		position /= FVector(101.0, 110.0, 0.0);
		return (position.X * 9) + (position.Y);
	}

	void DownPiecies(int index);
	void MovePiecies(int thisIndex, int moveIndex);

private:
	UFUNCTION()
		void DownBoard(TArray<int32> moveIndex, int32 Position);
	UFUNCTION()
	void UpBoard(TArray<int32> moveIndex, int32 Position);
	UFUNCTION()
		void ShowPowerHealthMouseOver(UPrimitiveComponent* TouchedComponent);
	UFUNCTION()
		void EndMouseOver(UPrimitiveComponent* TouchedComponent);
};
