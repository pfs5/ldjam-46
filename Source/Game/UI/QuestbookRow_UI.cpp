// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "QuestbookRow_UI.h"
#include "../QuestSystem/Quest.h"
#include "Components/TextBlock.h"
/*----------------------------------------------------------------------------------------------------*/
UQuestbookRow_UI::UQuestbookRow_UI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}
//--------------------------------------------------------------------------------------------------
void UQuestbookRow_UI::Init(UQuest* quest)
{
	if (quest == nullptr)
	{
		return;
	}

	if (_questObjective == nullptr || _questTimer == nullptr)
	{
		return;
	}

	_questObjective->SetText(quest->GetObjective()._description);
	_questTimer->SetText(FText::AsNumber(quest->GetDeadline()));
}
/*----------------------------------------------------------------------------------------------------*/