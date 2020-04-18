// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "QuestManager.h"
#include "Engine/World.h"
#include "Game/OfficeZGameMode.h"
/*----------------------------------------------------------------------------------------------------*/
AQuestManager::AQuestManager()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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
void AQuestManager::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
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