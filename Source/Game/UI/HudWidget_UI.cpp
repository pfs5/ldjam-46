// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "HudWidget_UI.h"
#include "Quest_UI.h"
#include "QuestbookWidget.h"
/*----------------------------------------------------------------------------------------------------*/
UHudWidget_UI::UHudWidget_UI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}
//--------------------------------------------------------------------------------------------------
UQuest_UI* UHudWidget_UI::GetQuestUI() const
{
	return _questUI;
}
/*----------------------------------------------------------------------------------------------------*/
UQuestbookWidget* UHudWidget_UI::GetQuestbookWidget() const
{
	return _questbookWidget;
}
/*----------------------------------------------------------------------------------------------------*/
void UHudWidget_UI::ShowBossQuestDialogue(UQuest* quest)
{
	if (_questUI == nullptr)
	{
		return;
	}

	_questUI->ShowQuest(quest);

	_isDialogueOnScreen = true;
}
/*----------------------------------------------------------------------------------------------------*/
void UHudWidget_UI::HideBossQuestDialogue()
{
	if (_questUI == nullptr)
	{
		return;
	}

	_questUI->HideQuest();

	_isDialogueOnScreen = false;
}
/*----------------------------------------------------------------------------------------------------*/
bool UHudWidget_UI::IsDialogueOnScreen() const
{
	return _isDialogueOnScreen;
}
/*----------------------------------------------------------------------------------------------------*/
void UHudWidget_UI::AddActiveQuestToQuestbook(UQuest* quest)
{
	_questbookWidget->AddActiveQuest(quest);
}
/*----------------------------------------------------------------------------------------------------*/
void UHudWidget_UI::RemoveActiveQuestFromQuestbook(UQuest* quest)
{
	_questbookWidget->RemoveActiveQuest(quest);
}
/*----------------------------------------------------------------------------------------------------*/
void UHudWidget_UI::ToggleQuestbook()
{
	if (_questbookWidget == nullptr)
	{
		return;
	}

	_questbookWidget->ToggleQuestbook();
}
//--------------------------------------------------------------------------------------------------
void UHudWidget_UI::UpdateQuest(UQuest* quest)
{
	_questbookWidget->UpdateQuest(quest);
}
/*----------------------------------------------------------------------------------------------------*/