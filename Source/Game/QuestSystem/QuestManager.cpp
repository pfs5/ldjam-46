// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "QuestManager.h"
#include "Engine/World.h"
#include "Game/OfficeZGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Quest.h"
#include "../UI/OfficeZHUD.h"
#include "../UI/HudWidget_UI.h"
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

	_currentQuests.Add(quest);
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
			for(int32 i = _currentQuests.Num() - 1; i >= 0 ;--i)
			{
				UQuest* quest = _currentQuests[i];
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
					_currentQuests.Remove(quest);

					// Quest failed!!!
					_otkazMeter += quest->GetOzkazAddValue();

					// Check if player is fired
					if (ShouldFirePlayer())
					{
						// Fire player i.e. game over
					}
				}
			}
		}
	}
}
//--------------------------------------------------------------------------------------------------
bool AQuestManager::ShouldFirePlayer()
{
	std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
	return distribution(_randomEngine) <= _otkazMeter;
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