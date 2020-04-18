// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "QuestManager.h"
#include "Engine/World.h"
#include "Game/OfficeZGameMode.h"
/*----------------------------------------------------------------------------------------------------*/
AQuestManager::AQuestManager()
{
	PrimaryActorTick.bCanEverTick = true;
}
/*----------------------------------------------------------------------------------------------------*/
void AQuestManager::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}
/*----------------------------------------------------------------------------------------------------*/
void AQuestManager::CreateQuest()
{

}
/*----------------------------------------------------------------------------------------------------*/
void AQuestManager::RemoveQuest(UQuest* quest)
{

}
/*----------------------------------------------------------------------------------------------------*/
void AQuestManager::OnQuestCreated()
{

}
/*----------------------------------------------------------------------------------------------------*/
void AQuestManager::OnQuestRemoved()
{

}
/*----------------------------------------------------------------------------------------------------*/
void AQuestManager::BeginPlay()
{
	Super::BeginPlay();
}
/*----------------------------------------------------------------------------------------------------*/
void AQuestManager::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	Super::EndPlay(endPlayReason);
}
/*----------------------------------------------------------------------------------------------------*/
AQuestManager* GetQuestManager(const UObject* worldContextObject)
{
	if (worldContextObject == nullptr)
	{
		return nullptr;
	}
	UWorld* world = worldContextObject->GetWorld();
	if (world == nullptr)
	{
		return nullptr;
	}
	AOfficeZGameMode* gameMode = Cast<AOfficeZGameMode>(world->GetAuthGameMode());
	if (gameMode == nullptr)
	{
		return nullptr;
	}
	return gameMode->GetQuestManager();
}
/*----------------------------------------------------------------------------------------------------*/