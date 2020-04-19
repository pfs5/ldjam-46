// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HudWidget_UI.generated.h"
/*----------------------------------------------------------------------------------------------------*/
class UTextBlock;
class UQuest;
class UQuestbookWidget;
class UQuest_UI;
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class GAME_API UHudWidget_UI : public UUserWidget
{
	GENERATED_BODY()

public:
	UHudWidget_UI(const FObjectInitializer& ObjectInitializer);

	UQuest_UI* GetQuestUI() const;
	UQuestbookWidget* GetQuestbookWidget() const;

	void ShowBossQuestDialogue(UQuest* quest);
	void HideBossQuestDialogue();
	bool IsDialogueOnScreen() const;

	void AddActiveQuestToQuestbook(UQuest* quest);
	void RemoveActiveQuestFromQuestbook(UQuest* quest);

	void ToggleQuestbook();

private:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UQuest_UI* _questUI;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UQuestbookWidget* _questbookWidget;

	bool _isDialogueOnScreen = false;
};
/*----------------------------------------------------------------------------------------------------*/