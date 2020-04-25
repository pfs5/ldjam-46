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
	Update(quest, quest->GetDeadline());
}
//--------------------------------------------------------------------------------------------------
void UQuestbookRowWidget::Update(const UQuest* quest, float time)
{
	if (quest == nullptr)
	{
		return;
	}

	if (_questObjective == nullptr || _questTimer == nullptr)
	{
		return;
	}

	_questObjective->SetText(quest->GetObjective()._description.ToUpper());

	int32 currentTime = FGenericPlatformMath::RoundToInt(time);

	if(currentTime == _lastTime)
	{
		return;
	}

	if (currentTime <= 0)
	{
		currentTime = 0;
	}
	
	_questTimer->SetText(FText::AsNumber(currentTime));

	_lastTime = currentTime;
}
//--------------------------------------------------------------------------------------------------
void UQuestbookRowWidget::FinishObjective()
{
	_questObjective->SetStrikeBrush(_strikeBrush);
}
/*----------------------------------------------------------------------------------------------------*/