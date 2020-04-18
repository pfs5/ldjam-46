// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "OfficeZGameMode.h"
#include "Engine/World.h"
#include "QuestSystem/QuestManager.h"
/*----------------------------------------------------------------------------------------------------*/
AOfficeZGameMode::AOfficeZGameMode()
{
	_questManagerClass = AQuestManager::StaticClass();
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (_questManagerClass != nullptr)
	{
		_questManager = GetWorld()->SpawnActor<AQuestManager>(_questManagerClass);
	}
}
/*----------------------------------------------------------------------------------------------------*/
AQuestManager* AOfficeZGameMode::GetQuestManager() const
{
	return _questManager;
}
/*----------------------------------------------------------------------------------------------------*/
