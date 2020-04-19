// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "QuestbookWidget.h"
#include "../QuestSystem/Quest.h"
/*----------------------------------------------------------------------------------------------------*/
UQuestbookWidget::UQuestbookWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}
/*----------------------------------------------------------------------------------------------------*/
void UQuestbookWidget::AddActiveQuest(UQuest* quest)
{

}
/*----------------------------------------------------------------------------------------------------*/
void UQuestbookWidget::RemoveActiveQuest(UQuest* quest)
{

}
/*----------------------------------------------------------------------------------------------------*/
void UQuestbookWidget::ToggleQuestbook()
{
	if (_isOpened)
	{
		SetVisibility(ESlateVisibility::Hidden);
		_isOpened = false;
	}
	else
	{
		SetVisibility(ESlateVisibility::Visible);
		_isOpened = true;
	}
}
/*----------------------------------------------------------------------------------------------------*/