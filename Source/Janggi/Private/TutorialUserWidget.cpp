#include "TutorialUserWidget.h"
#include "TutorialJanggiBoard.h"

#include <Components/TextBlock.h>
#include <Components/Button.h>
#include <Components/TextBlock.h>
#include <Components/Image.h>
#include "Animation/WidgetAnimation.h"

#include "Kismet/GameplayStatics.h"

void UTutorialUserWidget::NativeConstruct()
{
	NextButton->OnClicked.AddDynamic(this, &UTutorialUserWidget::CallBack_NextButton);
	PreviousButton->OnClicked.AddDynamic(this, &UTutorialUserWidget::CallBack_PreviousButton);
	MainButton->OnClicked.AddDynamic(this, &UTutorialUserWidget::CallBack_MainButton);
	ResetButton->OnClicked.AddDynamic(this, &UTutorialUserWidget::CallBack_ResetButton);

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATutorialJanggiBoard::StaticClass(), OutActors);
	for (AActor* a : OutActors)
	{
		JanggiBoard = Cast<ATutorialJanggiBoard>(a);
	}
}

void UTutorialUserWidget::CallBack_NextButton()
{
	tutoraialIndex++;
	if (tutoraialIndex >= tutorialLines.Num()) // 배열 범위 넘어갈 경우
	{
		tutoraialIndex--;
		return;
	}

	switch (tutoraialIndex)
	{
	case 0:
		PreviousButton->SetVisibility(ESlateVisibility::Hidden);
		break;
	case 1:
		TurnImage->SetVisibility(ESlateVisibility::Hidden);
		/// <summary>
		/// 
		/// </summary>
		PreviousButton->SetVisibility(ESlateVisibility::Visible);
		break;
	case 2:
		EnemyTimeImage->SetVisibility(ESlateVisibility::Hidden);
		MyTimeImage->SetVisibility(ESlateVisibility::Hidden);
		PowerHealthImage->SetVisibility(ESlateVisibility::Hidden);

		TurnImage->SetVisibility(ESlateVisibility::HitTestInvisible);
		PlayAnimation(TurnAim);
		break;
	case 3:
		TurnImage->SetVisibility(ESlateVisibility::Hidden);
		EnemyTimeImage->SetVisibility(ESlateVisibility::Hidden);
		MyTimeImage->SetVisibility(ESlateVisibility::Hidden);

		PowerHealthImage->SetVisibility(ESlateVisibility::HitTestInvisible);
		PlayAnimation(PowerHealthAim);
		break;
	case 4:
		PowerHealthImage->SetVisibility(ESlateVisibility::Hidden);

		EnemyTimeImage->SetVisibility(ESlateVisibility::HitTestInvisible);
		MyTimeImage->SetVisibility(ESlateVisibility::HitTestInvisible);
		PlayAnimation(EnemyTimeAim);
		PlayAnimation(MyTimeAim);
		break;
	case 5:
		MyTimeImage->SetVisibility(ESlateVisibility::Hidden);
		EnemyTimeImage->SetVisibility(ESlateVisibility::Hidden);
		break;
	case 6:
		Arrow1Image->SetVisibility(ESlateVisibility::Hidden);
		break;
	case 7:
		KnightImage->SetVisibility(ESlateVisibility::Hidden);

		Arrow1Image->SetVisibility(ESlateVisibility::HitTestInvisible);
		PlayAnimation(Arrow1Aim);
		break;
	case 8:
		Arrow1Image->SetVisibility(ESlateVisibility::Hidden);

		KnightImage->SetVisibility(ESlateVisibility::HitTestInvisible);
		PlayAnimation(KnightAim);
		break;
	case 9:
		KnightImage->SetVisibility(ESlateVisibility::Hidden);
		Arrow2Image->SetVisibility(ESlateVisibility::Hidden);
		KingImage->SetVisibility(ESlateVisibility::Hidden);
		break;
	case 10:
		TurnImage->SetVisibility(ESlateVisibility::Hidden);

		TurnTextBlock->SetText(FText::FromString("1"));
		Arrow2Image->SetVisibility(ESlateVisibility::HitTestInvisible);
		PlayAnimation(Arrow2Aim);
		KingImage->SetVisibility(ESlateVisibility::HitTestInvisible);
		PlayAnimation(KingAim);
		break;
	case 11:
		KingImage->SetVisibility(ESlateVisibility::Hidden);
		PieciesImage->SetVisibility(ESlateVisibility::Hidden);

		Arrow2Image->SetVisibility(ESlateVisibility::HitTestInvisible);
		TurnTextBlock->SetText(FText::FromString("16"));
		TurnImage->SetVisibility(ESlateVisibility::HitTestInvisible);
		PlayAnimation(TurnAim);
		break;
	case 12:
		Arrow2Image->SetVisibility(ESlateVisibility::Hidden);
		TurnImage->SetVisibility(ESlateVisibility::Hidden);

		PieciesImage->SetVisibility(ESlateVisibility::HitTestInvisible);
		PlayAnimation(PieciesAim);
		TurnTextBlock->SetText(FText::FromString("1"));

		break;
	case 13:
		PieciesImage->SetVisibility(ESlateVisibility::Hidden);
		KingImage->SetVisibility(ESlateVisibility::Hidden);
		Arrow2Image->SetVisibility(ESlateVisibility::Hidden);

		TurnTextBlock->SetText(FText::FromString("11"));
		TurnImage->SetVisibility(ESlateVisibility::HitTestInvisible);
		PlayAnimation(TurnAim);
		break;
	case 14:
		TurnImage->SetVisibility(ESlateVisibility::Hidden);

		Arrow2Image->SetVisibility(ESlateVisibility::HitTestInvisible);
		PlayAnimation(Arrow2Aim);
		KingImage->SetVisibility(ESlateVisibility::HitTestInvisible);
		PlayAnimation(KingAim);
		TurnTextBlock->SetText(FText::FromString("1"));

		break;
	case 15:
		Arrow2Image->SetVisibility(ESlateVisibility::Hidden);
		MainButton->SetVisibility(ESlateVisibility::Hidden);

		TurnTextBlock->SetText(FText::FromString("16"));
		NextButton->SetVisibility(ESlateVisibility::Visible);

		PlayAnimation(KingAim);
		break;
	case 16:
		TurnTextBlock->SetText(FText::FromString("17"));

		KingImage->SetVisibility(ESlateVisibility::HitTestInvisible);
		PlayAnimation(KingAim);
		break;
	case 17:
		KingImage->SetVisibility(ESlateVisibility::Hidden);
		SkillButton->SetVisibility(ESlateVisibility::Hidden);
		SkillButtonImage->SetVisibility(ESlateVisibility::Hidden);
		break;
	case 18:
		SkillTextBlock1->SetVisibility(ESlateVisibility::Hidden);
		SkillTextBlock->SetVisibility(ESlateVisibility::Hidden);
		SkillImage->SetVisibility(ESlateVisibility::Hidden);

		SkillButton->SetVisibility(ESlateVisibility::Visible);
		SkillButtonImage->SetVisibility(ESlateVisibility::Visible);
		PlayAnimation(SkillButtonAim);
		break;
	case 19:
		SkillButtonImage->SetVisibility(ESlateVisibility::Hidden);

		SkillTextBlock1->SetVisibility(ESlateVisibility::Visible);
		SkillTextBlock->SetVisibility(ESlateVisibility::Visible);
		SkillImage->SetVisibility(ESlateVisibility::Visible);
		PlayAnimation(SkillAim);
		break;
	case 20:
		SkillImage->SetVisibility(ESlateVisibility::Hidden);
		break;
	case 21:
		break;
	case 22:
		MainButton->SetVisibility(ESlateVisibility::Hidden);
		ResetButton->SetVisibility(ESlateVisibility::Hidden);

		NextButton->SetVisibility(ESlateVisibility::Visible);
		SkillButton->SetVisibility(ESlateVisibility::Visible);
		break;
	case 23:
		KingImage->SetVisibility(ESlateVisibility::Hidden);
		NextButton->SetVisibility(ESlateVisibility::Hidden);
		SkillButton->SetVisibility(ESlateVisibility::Hidden);

		MainButton->SetVisibility(ESlateVisibility::Visible);
		ResetButton->SetVisibility(ESlateVisibility::Visible);
		break;
	default:
		break;
	}

	TutoralTextBlock->SetText(FText::FromString(tutorialLines[tutoraialIndex]));
	JanggiBoard->TutorialFlow(tutoraialIndex);
}

void UTutorialUserWidget::CallBack_PreviousButton()
{
	tutoraialIndex -= 2;
	if (tutoraialIndex < 0) // 배열 범위가 음수 일 경우
	{
		tutoraialIndex = -1;
	}

	CallBack_NextButton();
}

void UTutorialUserWidget::CallBack_MainButton()
{
	UGameplayStatics::OpenLevel(this, FName(TEXT("Server")));
}

void UTutorialUserWidget::CallBack_ResetButton()
{
	MainButton->SetVisibility(ESlateVisibility::Hidden);
	ResetButton->SetVisibility(ESlateVisibility::Hidden);
	NextButton->SetVisibility(ESlateVisibility::Visible);
	tutoraialIndex = -1;
	CallBack_NextButton();
}
