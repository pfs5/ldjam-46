// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "OfficeZBoss.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PaperFlipbookComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "../QuestSystem/QuestManager.h"
#include "../UI/OfficeZHUD.h"
#include "Kismet/GameplayStatics.h"
#include "../UI/HudWidget_UI.h"
#include "../Interactables/Door.h"
#include "../Player/OfficeZPlayerController.h"
/*----------------------------------------------------------------------------------------------------*/
AOfficeZBoss::AOfficeZBoss()
{
	PrimaryActorTick.bCanEverTick = true;

	_nextQuestTimer = 3.0f;
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZBoss::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	AOfficeZPlayerController* playerController = Cast<AOfficeZPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (playerController == nullptr)
	{
		return;
	}

	if (!playerController->IsGameStarted() && !playerController->IsTutorialDone())
	{
		return;
	}

	AOfficeZHUD* hud = Cast<AOfficeZHUD>(playerController->GetHUD());
	if (hud != nullptr)
	{
		UHudWidget_UI* hudWidget = hud->GetHudWidget();
		if (hudWidget != nullptr)
		{
			if (hudWidget->IsDialogueOnScreen())
			{
				_dialogueOnScreenTimer += deltaTime;

				if (_dialogueOnScreenTimer > _dialogueOnScreenTime)
				{
					HideBoss();

					_dialogueOnScreenTimer = 0;
				}
			}
		}
	}

/*	if (IsPendingQuest())
	{
		return;
	}
*/
	if (_nextQuestTimer <= 0.0f)
	{
		AQuestManager* questManager = GetQuestManager(this);
		if (questManager == nullptr)
		{
			return;
		}

		if (questManager->GetNumActiveQuests() >= _availableQuests.Num())
		{
			return;
		}

		_numPendingQuests++;
		SetIsPendingQuest(true);

		_nextQuestTimer = UKismetMathLibrary::RandomFloatInRange(_minTimeBetweenQuests, _maxTimeBetweenQuests);
	}
	else
	{
		_nextQuestTimer -= deltaTime;
	}
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZBoss::SetIsPendingQuest(bool value)
{
	if (_pendingQuest == value)
	{
		return;
	}

	_pendingQuest = value;

	OnIsPendingQuestChanged();
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZBoss::OnIsPendingQuestChanged()
{
	AOfficeZHUD* hud = Cast<AOfficeZHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	if (hud != nullptr)
	{
		UHudWidget_UI* hudWidget = hud->GetHudWidget();
		if (hudWidget != nullptr)
		{
			hudWidget->ShowNotification();
		}
	}
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZBoss::CreateQuest()
{
	if (_availableQuests.Num() == 0)
	{
		return;
	}

	if (_numPendingQuests <= 0)
	{
		return;
	}

	AQuestManager* questManager = GetQuestManager(this);
	if (questManager == nullptr)
	{
		return;
	}

	_numPendingQuests--;

	int maxTries = 100;
	bool success = false;
	int randomQuestIndex = 0;
	while (maxTries-- > 0)
	{
		randomQuestIndex = UKismetMathLibrary::RandomIntegerInRange(0, _availableQuests.Num() - 1);
		if (questManager->CanAddQuest(_availableQuests[randomQuestIndex]))
		{
			success = true;
			break;
		}
	}

	if (!success || !_availableQuests.IsValidIndex(randomQuestIndex))
	{
		return;
	}

	questManager->AddActiveQuest(_availableQuests[randomQuestIndex]);

	_pendingQuests.Add(_availableQuests[randomQuestIndex]);

	//_availableQuests.RemoveAt(randomQuestIndex);
}
/*----------------------------------------------------------------------------------------------------*/
bool AOfficeZBoss::IsPendingQuest() const
{
	return _pendingQuest;
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZBoss::HideBoss()
{
	AOfficeZHUD* hud = Cast<AOfficeZHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	if (hud != nullptr)
	{
		UHudWidget_UI* hudWidget = hud->GetHudWidget();
		if (hudWidget != nullptr)
		{
			hudWidget->HideBossQuestDialogue();
			_dialogueOnScreenTimer = 0.0f;

			if (!IsPendingQuest())
			{
				hudWidget->HideNotification();
			}

			SetActorLocation(FVector(10000.0f, 0.0f, 10000.0f));

		}
	}

	if (_door != nullptr)
	{
		_door->HideOpenDoor();
	}
}
/*----------------------------------------------------------------------------------------------------*/
int32 AOfficeZBoss::GetNumPendingQuests() const
{
	return _numPendingQuests;
}
/*----------------------------------------------------------------------------------------------------*/
bool AOfficeZBoss::ShowNextBossDialogue()
{
	if (_pendingQuests.Num() == 0)
	{
		return false;
	}

	AOfficeZHUD* hud = Cast<AOfficeZHUD>(UGameplayStatics::GetPlayerController(this->GetOwner(), 0)->GetHUD());
	if (hud != nullptr)
	{
		UHudWidget_UI* hudWidget = hud->GetHudWidget();
		if (hudWidget != nullptr)
		{
			hudWidget->ShowBossQuestDialogue(_pendingQuests[0]);
			_pendingQuests.RemoveAt(0);

			if (_pendingQuests.Num() == 0)
			{
				SetIsPendingQuest(false);
			}
		}
	}

	return true;
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZBoss::BeginPlay()
{
	Super::BeginPlay();
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZBoss::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	Super::EndPlay(endPlayReason);
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZBoss::OnQuestCreated()
{

}
/*----------------------------------------------------------------------------------------------------*/