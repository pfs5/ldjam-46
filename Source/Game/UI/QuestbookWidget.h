// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestbookRowWidget.h"
#include "QuestbookWidget.generated.h"
/*----------------------------------------------------------------------------------------------------*/
class UQuest;
class UScrollBox;
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class GAME_API UQuestbookWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UQuestbookWidget(const FObjectInitializer& ObjectInitializer);

	void AddActiveQuest(UQuest* quest);
	void RemoveActiveQuest(UQuest* quest, bool success);
	void UpdateQuest(UQuest* quest, float time);
	void ToggleQuestbook();

	UFUNCTION(BlueprintImplementableEvent)
	void ScrollMoveUp();

	UFUNCTION(BlueprintImplementableEvent)
	void ScrollMoveDown();

private:
	bool _isOpened = false;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> _questbookRowWidgetClass;

	//UPROPERTY(meta = (BindWidget, AllowPrivateAcces = "true"))
	//UScrollBox* _scrollbox;

	UPROPERTY(meta = (BindWidget, AllowPrivateAcces = "true"))
	class UVerticalBox* _questItemsVB;

	TMap<FString, UQuestbookRowWidget*> _activeQuestRows;
};
/*----------------------------------------------------------------------------------------------------*/