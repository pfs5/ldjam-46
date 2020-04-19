// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "QuestbookRowWidget.h"
#include "../QuestSystem/Quest.h"
#include "Components/TextBlock.h"
/*----------------------------------------------------------------------------------------------------*/
UQuestbookRowWidget::UQuestbookRowWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}
//--------------------------------------------------------------------------------------------------
void UQuestbookRowWidget::Init(const UQuest* quest)
{
	Update(quest);
}
//--------------------------------------------------------------------------------------------------
void UQuestbookRowWidget::Update(const UQuest* quest)
{
	if (quest == nullptr)
	{
		return;
	}

	if (_questObjective == nullptr || _questTimer == nullptr)
	{
		return;
	}

	int32 time = FGenericPlatformMath::RoundToInt(quest->GetDeadline());

	if(time == _lastTime)
	{
		return;
	}

	if (time <= 0)
	{
		time = 0;
	}

	_questObjective->SetText(quest->GetObjective()._description);
	_questTimer->SetText(FText::AsNumber(time));

	_lastTime = time;
}
/*----------------------------------------------------------------------------------------------------*/