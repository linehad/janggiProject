// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Board.generated.h"

UCLASS()
class JANGGI_API ABoard : public AActor
{
	GENERATED_BODY()
private:
	float SoundEffectVol = 3.0f;
	TArray<int32> moveIndex;

	UMaterial* fieldGoldsMaterial = nullptr;
	UMaterial* fieldWoodsMaterial = nullptr;

	bool bIsDestroy = false;
	bool usingSkill = false;
	int32 showHealthPos = 0;
	int32 skillCount = 3;
	class ASoundManager* SoundManager = nullptr;
	class AJanggiPlayerController* JanggiController = nullptr;
protected:

	// Called when the game starts or when spawned
	UPROPERTY(BlueprintReadOnly, Category = "BoardVal")
	class AJanggiGameStateBase* JanggiState = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = "BoardVal")
		TArray<UStaticMeshComponent*> fliedsMesh;
	UPROPERTY(BlueprintReadWrite, Category = "BoardVal")
		TArray<UStaticMeshComponent*> pieciesMesh;
	UPROPERTY(BlueprintReadWrite, Category = "BoardVal")
		TArray<UStaticMeshComponent*> fillPieciesMesh;
	UPROPERTY(BlueprintReadWrite, Category = "BoardVal")
		TArray<class AExplosion*> explosionArr;

	UPROPERTY(BlueprintReadWrite, Category = "BoardVal")
		UMaterial* fieldsMaterial = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = "BoardVal")
		int32 lastClick = -1;
	UPROPERTY(BlueprintReadWrite, Category = "BoardVal")
		int32 curPosition = -1; //리플리케이션 할 것임
	UPROPERTY(BlueprintReadWrite, Category = "BoardVal")
	bool gameTurn = true;

	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category = "BoardVal")
		void SetJanggiStaticMesh(int32 index, UStaticMeshComponent* piecies, UStaticMeshComponent* fillPiecies)
	{
		pieciesMesh[index] = piecies;
		fillPieciesMesh[index] = fillPiecies;
	}

	UFUNCTION(BlueprintCallable, Category = "BoardVal")
		void SetbIsDestroy(bool IsDestroy)
	{
		bIsDestroy = IsDestroy;
	}
public:
	// Sets default values for this actor's properties
	ABoard();

	UFUNCTION(BlueprintCallable, Category = "BoardVal")
		void BP_CkeckMove() { ChkeckMove(); } // 블루프린트에서 RPC 호출
	UFUNCTION(BlueprintCallable, Category = "BoardVal")
		void BP_IsMove() { IsMove(); } // 블루프린트에서 RPC 호출
	UFUNCTION(BlueprintCallable, Category = "BoardVal")
		void BP_JanggiDestroyComponent(int32 DestroyPos);
	UFUNCTION(BlueprintCallable, Category = "BoardVal")
		void SetLastClick(int32 position) { lastClick = position; }

	UFUNCTION(BlueprintImplementableEvent)
		void BP_StartEvent();
	UFUNCTION(BlueprintImplementableEvent)
		void BP_ResurrectionEvent();
	UFUNCTION()
		void SetMouseOver();
	UFUNCTION()
	void ReStart();
private:
	UFUNCTION()
		void ShowPowerHealthMouseOver(UPrimitiveComponent* TouchedComponent);
	UFUNCTION()
		void EndMouseOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
		void JanggiDestroy(int32 DestroyPos);

	UFUNCTION()
		void SetMovePiecies(); // 말이 이동한 뒤 배열 세팅
	UFUNCTION()
		void ChkeckMove();  // 블루프린트에서 RPC 호출
	UFUNCTION()
		void IsMove(); // 블루프린트에서 RPC 호출
	
	FVector IndexToPosition(int index) { return FVector((index / 9) * 101.0, (index % 9) * 110.0, 0.0); }
	int32 PositionToIndex(FVector position) 
	{ 
		position /= FVector(101.0, 110.0, 0.0);
		return (position.X * 9) + (position.Y);
	}
};
