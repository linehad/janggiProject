// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class JANGGI_API UServerUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
		class UButton* ServerButton = nullptr;
	UPROPERTY(meta = (BindWidget))
		class UButton* ClientButton = nullptr;
	UPROPERTY(meta = (BindWidget))
		class UButton* EndButton = nullptr;
	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* ip_EditableTextBox = nullptr;
	UPROPERTY(meta = (BindWidget))
		class UButton* Tutorial_Button = nullptr;
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
		void ServerButtonCallback();
	UFUNCTION()
		void ClientButtonCallback();
	UFUNCTION()
		void IP_EditableTextBoxCallback(const FText& Text);

	UFUNCTION()
		void TutorialButtonCallback();
	UFUNCTION()
		void EndButtonCallback();
};
