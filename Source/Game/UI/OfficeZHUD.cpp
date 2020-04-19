// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "OfficeZHUD.h"
#include "Quest_UI.h"
#include "../QuestSystem/Quest.h"
#include "HudWidget_UI.h"
/*----------------------------------------------------------------------------------------------------*/
AOfficeZHUD::AOfficeZHUD()
{
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZHUD::DrawHUD()
{
	Super::DrawHUD();
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZHUD::BeginPlay()
{
	Super::BeginPlay();

	if (_hudWidgetClass != nullptr)
	{
		_hudWidget = CreateWidget<UHudWidget_UI>(GetWorld(), _hudWidgetClass);
		if (_hudWidget != nullptr)
		{
			_hudWidget->AddToViewport();
		}
	}
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZHUD::ShowBossQuestDialogue(UQuest* quest)
{
	if (_hudWidget == nullptr)
	{
		return;
	}

	UQuest_UI* questUI = _hudWidget->GetQuestUI();
	if (questUI == nullptr)
	{
		return;
	}

	questUI->ShowQuest(quest);
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZHUD::HideBossQuestDialogue()
{
	if (_hudWidget == nullptr)
	{
		return;
	}

	UQuest_UI* questUI = _hudWidget->GetQuestUI();
	if (questUI == nullptr)
	{
		return;
	}

	questUI->HideQuest();
}
/*----------------------------------------------------------------------------------------------------*/