// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "QuestManager.h"
#include "Engine/World.h"
#include "Game/OfficeZGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Quest.h"
#include "../UI/OfficeZHUD.h"
#include "../UI/HudWidget_UI.h"
#include "../Interactables/Door.h"
/*----------------------------------------------------------------------------------------------------*/
AQuestManager::AQuestManager()
{
	PrimaryActorTick.bCanEverTick = true;
}
/*----------------------------------------------------------------------------------------------------*/
void AQuestManager::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	UpdateQuests(deltaTime);
}
/*----------------------------------------------------------------------------------------------------*/
void AQuestManager::AddActiveQuest(UQuest* quest)
{
	_activeQuests.Add(quest);

	AOfficeZHUD* hud = Cast<AOfficeZHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	if (hud != nullptr)
	{
		UHudWidget_UI* hudWidget = hud->GetHudWidget();
		if (hudWidget != nullptr)
		{
			hudWidget->AddActiveQuestToQuestbook(quest);
		}
	}
}
/*----------------------------------------------------------------------------------------------------*/
void AQuestManager::RemoveActiveQuest(UQuest* quest)
{
	_activeQuests.Remove(quest);

	AOfficeZHUD* hud = Cast<AOfficeZHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	if (hud != nullptr)
	{
		UHudWidget_UI* hudWidget = hud->GetHudWidget();
		if (hudWidget != nullptr)
		{
			hudWidget->RemoveActiveQuestFromQuestbook(quest);
		}
	}
}
/*----------------------------------------------------------------------------------------------------*/
void AQuestManager::OnActiveQuestCreated()
{

}
/*----------------------------------------------------------------------------------------------------*/
void AQuestManager::OnActiveQuestRemoved()
{

}
//--------------------------------------------------------------------------------------------------
void AQuestManager::UpdateQuests(float deltaTime)
{
	AOfficeZHUD* hud = Cast<AOfficeZHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	if (hud != nullptr)
	{
		UHudWidget_UI* hudWidget = hud->GetHudWidget();
		if (hudWidget != nullptr)
		{
			for (UQuest* quest : _currentQuests)
			{
				quest->SetDeadline(quest->GetDeadline() - deltaTime);
				hudWidget->UpdateQuest(quest);

				if (quest->GetDeadline() <= 0)
				{
					// Quest failed!!!
				}
			}
		}
	}

	
}
/*----------------------------------------------------------------------------------------------------*/
void AQuestManager::OnPlayerInteractedWith(AActor* target)
{
	for (int i = 0; i < _activeQuests.Num(); ++i)
	{
		if (target->GetClass() == ADoor::StaticClass())
		{

		}

		TSubclassOf<AActor> actorClass = _activeQuests[i]->GetObjective()._target;
		if(actorClass == target->GetClass())
		{

		}
	}
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