// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "HudWidget_UI.h"
#include "Quest_UI.h"
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