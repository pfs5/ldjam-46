// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "OfficeZHUD.h"
#include "Quest_UI.h"
#include "../QuestSystem/Quest.h"
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

	if (_questUIClass != nullptr)
	{
		_questUI = CreateWidget<UQuest_UI>(GetWorld(), _questUIClass);
		if (_questUI != nullptr)
		{
			_questUI->AddToViewport();
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
	if (_questUI == nullptr)
	{
		return;
	}

	_questUI->ShowQuest(quest);
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZHUD::HideBossQuestDialogue()
{
	if (_questUI == nullptr)
	{
		return;
	}

	_questUI->HideQuest();
}
/*----------------------------------------------------------------------------------------------------*/