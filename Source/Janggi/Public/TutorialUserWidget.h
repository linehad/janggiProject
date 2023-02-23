// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TutorialUserWidget.generated.h"

UCLASS()
class JANGGI_API UTutorialUserWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	class ATutorialJanggiBoard* JanggiBoard;

	int tutoraialIndex = 0;
	TArray<FString> tutorialLines
	{
		FString(TEXT("1. 튜토리얼에 오신것을 환영합니다!")),
		FString(TEXT("2. 기본적인 UI설명 입니다.")),
		FString(TEXT("3. 좌측 상단에는 게임 턴이 있습니다\n 자신이 몇 번째 턴을 맞이하고\n 있는지 알려주는 기능입니다.")),
		FString(TEXT("4. 바로 아래에선 장기말의\n체력과 공격력을 알려줍니다.\n 마우스를 기물 위에 가져다 놓으면\n해당 기물의 공격력과 남은 체력을 표시해 줍니다.\n")),
		FString(TEXT("5. 우측 상하단에는 남은 시간을 알려줍니다.\n시간은 총 15분 장기의 기본 시간입니다.\n\n 시간이 전부 소모 되었을 경우\n 시간패 혹은 시간승으로 게임이 끝나게 되니\n 시간에 유의하여 주시기 바랍니다.")),
		FString(TEXT("6. 해당 게임은 기본적으로 장기의 룰을 따릅니다.\n 하지만 각 말은 체력과 공격력을 가지고 있습니다.\n 기물들의 체력은 모두 14 입니다.")),
		FString(TEXT("7. 각 기물의 공격력 입니다.\n 차 : 5\n 마 : 7 \n상 : 11 \n 포 : 13 \n 졸 : 13 \n 사 : 14 \n 궁 : 14")),
		FString(TEXT("8. 공격을 하여 상대 기물을 죽이지 못하면\n공격당한 기물의 체력이 공격한 기물의\n 공격력 만큼 줄어들게 됩니다.\n\n이후 공격턴이 상대에게 넘어가고 \n공격한 기물은 제자리에 있게 됩니다.")),
		FString(TEXT("9. 상대 기물을 파괴할 경우 그 위치로 이동합니다.")),
		FString(TEXT("10. 기물 중 졸과 사는 부활하는 기물입니다.")),
		FString(TEXT("11. 졸은 죽은 위치에서 자신의 진영쪽으로\n 한 칸 이동하여 부활합니다.")),
		FString(TEXT("12. 죽었을 경우 15턴 뒤에 부활합니다.")),
		FString(TEXT("13. 사는 죽은 위치에서 부활합니다.")),
		FString(TEXT("14. 죽었을 경우 10턴 뒤에 부활합니다.")),
		FString(TEXT("15. 부활하는 기물은 부활하는 \n위치에 있는 모든 기물을 파괴하며 부활합니다.")),
		FString(TEXT("16. 부활 기물이 죽었을 경우 \n아군이 죽지 않게 조심하세요.")),
		FString(TEXT("17. 이 공격으로 부활기물을 죽일 경우\n부활을 저지할 수 있습니다.")),
		FString(TEXT("18. 마, 상, 졸에는\n스킬이 있습니다.")),
		FString(TEXT("19. 스킬 버튼을 누르고 기물을\n클릭하면 스킬을 사용할 수 있습니다.")),
		FString(TEXT("20. 스킬을 사용하면 사용가능한\n스킬의 개수가 줄어듭니다.")),
		FString(TEXT("21. 마는 스킬을 사용하면\n직선으로 움직입니다.")),
		FString(TEXT("22. 상은 스킬을 사용하면\n길을 가로막는 것들을 무시합니다.")),
		FString(TEXT("23. 졸은 스킬을 사용하면\n모든 방향으로 움직입니다.")),
		FString(TEXT("이제 시작해 볼까요?")),
	};

protected:
	// 버튼 들
	UPROPERTY(meta = (BindWidget))
		class UButton* NextButton = nullptr;
	UPROPERTY(meta = (BindWidget))
		class UButton* PreviousButton = nullptr;
	UPROPERTY(meta = (BindWidget))
		class UButton* MainButton = nullptr;
	UPROPERTY(meta = (BindWidget))
		class UButton* ResetButton = nullptr;
	UPROPERTY(meta = (BindWidget))
		class UButton* SkillButton = nullptr;

	// 텍스트들
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TutoralTextBlock = nullptr;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TurnTextBlock = nullptr;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* SkillTextBlock1 = nullptr;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* SkillTextBlock = nullptr;

	// 이미지들
	UPROPERTY(meta = (BindWidget))
		class UImage* TurnImage = nullptr;
	UPROPERTY(meta = (BindWidget))
		class UImage* EnemyTimeImage = nullptr;
	UPROPERTY(meta = (BindWidget))
		class UImage* MyTimeImage = nullptr;
	UPROPERTY(meta = (BindWidget))
		class UImage* Arrow1Image = nullptr;
	UPROPERTY(meta = (BindWidget))
		class UImage* Arrow2Image = nullptr;
	UPROPERTY(meta = (BindWidget))
		class UImage* PieciesImage = nullptr;
	UPROPERTY(meta = (BindWidget))
		class UImage* KingImage = nullptr;
	UPROPERTY(meta = (BindWidget))
		class UImage* KnightImage = nullptr;
	UPROPERTY(meta = (BindWidget))
		class UImage* PowerHealthImage = nullptr;
	UPROPERTY(meta = (BindWidget))
		class UImage* SkillButtonImage = nullptr;
	UPROPERTY(meta = (BindWidget))
		class UImage* SkillImage = nullptr;

	// 애니메이션들
	// Transient = 직렬화 해제 필요 없는 메모리를 차지하는 것을 막는다.
	UPROPERTY(Transient, meta = (BindWidgetAnim))
		class UWidgetAnimation* EnemyTimeAim = nullptr;
	UPROPERTY(Transient, meta = (BindWidgetAnim))
		class UWidgetAnimation* MyTimeAim = nullptr;
	UPROPERTY(Transient, meta = (BindWidgetAnim))
		class UWidgetAnimation* TurnAim = nullptr;
	UPROPERTY(Transient, meta = (BindWidgetAnim))
		class UWidgetAnimation* Arrow1Aim = nullptr;
	UPROPERTY(Transient, meta = (BindWidgetAnim))
		class UWidgetAnimation* Arrow2Aim = nullptr;
	UPROPERTY(Transient, meta = (BindWidgetAnim))
		class UWidgetAnimation* PieciesAim = nullptr;
	UPROPERTY(Transient, meta = (BindWidgetAnim))
		class UWidgetAnimation* KingAim = nullptr;
	UPROPERTY(Transient, meta = (BindWidgetAnim))
		class UWidgetAnimation* KnightAim = nullptr;
	UPROPERTY(Transient, meta = (BindWidgetAnim))
		class UWidgetAnimation* PowerHealthAim = nullptr;
	UPROPERTY(Transient, meta = (BindWidgetAnim))
		class UWidgetAnimation* SkillButtonAim = nullptr;
	UPROPERTY(Transient, meta = (BindWidgetAnim))
		class UWidgetAnimation* SkillAim = nullptr;
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
	void CallBack_NextButton();
	UFUNCTION()
	void CallBack_PreviousButton();
	UFUNCTION()
		void CallBack_MainButton();
	UFUNCTION()
		void CallBack_ResetButton();
};
