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

	_activeQuestRows.Add(quest->GetName().ToString(), widget);
}
/*----------------------------------------------------------------------------------------------------*/
void UQuestbookWidget::RemoveActiveQuest(UQuest* quest)
{
	if (quest == nullptr)
	{
		return;
	}

	UQuestbookRowWidget* widget = nullptr;

	for (auto& Elem : _activeQuestRows)
	{
		if (quest->GetName().ToString() == Elem.Key)
		{
			widget = Elem.Value;
		}
	}

	if (widget != nullptr)
	{
		_questItemsVB->RemoveChild(widget);
		_activeQuestRows.Remove(quest->GetName().ToString());
	}
}
//--------------------------------------------------------------------------------------------------
void UQuestbookWidget::UpdateQuest(UQuest* quest, float time)
{
	if (quest == nullptr)
	{
		return;
	}

	for (auto& Elem : _activeQuestRows)
	{
		if (quest->GetName().ToString() == Elem.Key)
		{
			if (Elem.Value != nullptr)
			{
				Elem.Value->Update(quest, time);
			}
				
		}
	}
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