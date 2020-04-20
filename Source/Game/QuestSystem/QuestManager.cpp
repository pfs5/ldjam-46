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
#include "../Interactables/NPCDialog.h"
#include "../Player/OfficeZPlayerController.h"
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
	if(quest == nullptr)
	{
		return;
	}

	_activeQuests.Add(quest);
	_questTiming.Add(quest, quest->GetDeadline());

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
int32 AQuestManager::GetNumActiveQuests() const
{
	return _activeQuests.Num();
}
/*----------------------------------------------------------------------------------------------------*/
bool AQuestManager::CanAddQuest(UQuest* quest) const
{
	for (const UQuest* q : _activeQuests)
	{
		if (q == quest)
		{
			return false;
		}
	}

	return true;
}
/*----------------------------------------------------------------------------------------------------*/
void AQuestManager::OnActiveQuestCreated()
{

}
/*----------------------------------------------------------------------------------------------------*/
void AQuestManager::OnActiveQuestRemoved()
{

}
//----------------------------------------------------------------------------------------------------*/
void AQuestManager::UpdateQuests(float deltaTime)
{
	AOfficeZHUD* hud = Cast<AOfficeZHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	if (hud != nullptr)
	{
		UHudWidget_UI* hudWidget = hud->GetHudWidget();
		if (hudWidget != nullptr)
		{
			for(int32 i = _activeQuests.Num() - 1; i >= 0 ;--i)
			{
				UQuest* quest = _activeQuests[i];
				if(quest == nullptr)
				{
					continue; 
				}

				_questTiming[quest] = _questTiming[quest] - deltaTime;

				if (_questTiming[quest] <= 0)
				{
					_questTiming[quest] = 0;
				}

				hudWidget->UpdateQuest(quest, _questTiming[quest]);

				if (_questTiming[quest] <= 0)
				{
					hudWidget->RemoveActiveQuestFromQuestbook(quest);
					_questTiming.Remove(quest);
					_activeQuests.Remove(quest);

					// Quest failed!!!
					_otkazMeter += quest->GetOzkazAddValue();

					// Check if player is fired
					if (ShouldFirePlayer())
					{
						// Fire player i.e. game over
						Cast<AOfficeZPlayerController>(UGameplayStatics::GetPlayerController(this, 0))->FinishGame();
						hudWidget->FinishGame();
					}
				}
			}
		}
	}	
}
//----------------------------------------------------------------------------------------------------*/
bool AQuestManager::ShouldFirePlayer()
{
	std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
	return distribution(_randomEngine) <= _otkazMeter;
}
/*----------------------------------------------------------------------------------------------------*/
bool AQuestManager::IsActorPartOfActiveQuest(const AActor* actor)
{
	for (int i = 0; i < _activeQuests.Num(); ++i)
	{
		TSubclassOf<AActor> actorClass = _activeQuests[i]->GetObjective()._target;
		if (actorClass == actor->GetClass())
		{
			return true;
		}
	}

	return false;
}
/*----------------------------------------------------------------------------------------------------*/
void AQuestManager::OnPlayerInteractedWith(AActor* target)
{
	for (int i = 0; i < _activeQuests.Num(); ++i)
	{
		TSubclassOf<AActor> actorClass = _activeQuests[i]->GetObjective()._target;
		if(actorClass == target->GetClass())
		{
			if (ANPCDialog* interactable = Cast<ANPCDialog>(target))
			{
				AOfficeZHUD* hud = Cast<AOfficeZHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
				if (hud != nullptr)
				{
					UHudWidget_UI* hudWidget = hud->GetHudWidget();
					if (hudWidget != nullptr)
					{
						hudWidget->ShowBossQuestDialogue(_activeQuests[i], true);
					}
				}
			}

			RemoveActiveQuest(_activeQuests[i]);
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