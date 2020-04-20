// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "Quest_UI.h"
#include "../QuestSystem/Quest.h"
#include "Components/TextBlock.h"
/*----------------------------------------------------------------------------------------------------*/
UQuest_UI::UQuest_UI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SetVisibility(ESlateVisibility::Hidden);
}
/*----------------------------------------------------------------------------------------------------*/
void UQuest_UI::ShowQuest(UQuest* quest)
{
	if (quest == nullptr || _questDescription == nullptr)
	{
		return;
	}

	SetVisibility(ESlateVisibility::Visible);

	_questDescription->SetText(quest->GetDescription().ToUpper());
}
/*----------------------------------------------------------------------------------------------------*/
void UQuest_UI::HideQuest()
{
	SetVisibility(ESlateVisibility::Hidden);
}
/*----------------------------------------------------------------------------------------------------*/