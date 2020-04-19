// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "QuestbookWidget.h"
#include "../QuestSystem/Quest.h"
#include "QuestbookRowWidget.h"
#include "Components/VerticalBox.h"
/*----------------------------------------------------------------------------------------------------*/
UQuestbookWidget::UQuestbookWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}
/*----------------------------------------------------------------------------------------------------*/
void UQuestbookWidget::AddActiveQuest(UQuest* quest)
{
	if (quest == nullptr)
	{
		return;
	}

	if (_questbookRowWidgetClass == nullptr)
	{
		return;
	}

	UQuestbookRowWidget* widget = CreateWidget<UQuestbookRowWidget>(GetWorld(), _questbookRowWidgetClass);
	if (widget == nullptr)
	{
		return;
	}

	widget->Init(quest);

	_questItemsVB->AddChildToVerticalBox(widget);

	_activeQuests.Add(_questItemsVB->GetChildIndex(widget));
}
/*----------------------------------------------------------------------------------------------------*/
void UQuestbookWidget::RemoveActiveQuest(UQuest* quest)
{
	if (quest == nullptr)
	{
		return;
	}

	int32 index = -1;

	for (auto& Elem : _activeQuests)
	{
		if (quest == Elem.Value)
		{
			index = Elem.Key;
		}
	}

	if (index > -1)
	{
		_questItemsVB->RemoveChildAt(index);
		_activeQuests.Remove(index);
	}
}
/*----------------------------------------------------------------------------------------------------*/