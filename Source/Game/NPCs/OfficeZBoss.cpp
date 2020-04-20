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
/*----------------------------------------------------------------------------------------------------*/
AOfficeZBoss::AOfficeZBoss()
{
	PrimaryActorTick.bCanEverTick = true;
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZBoss::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	AOfficeZHUD* hud = Cast<AOfficeZHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
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
					hudWidget->HideBossQuestDialogue();
					_dialogueOnScreenTimer = 0.0f;

					SetActorLocation(FVector(10000.0f, 0.0f, 10000.0f));

					_dialogueOnScreenTimer = 0;
				}
			}
		}
	}

	if (IsPendingQuest())
	{
		return;
	}

	if (_nextQuestTimer <= 0.0f)
	{
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
	// create notification
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZBoss::CreateQuest()
{
	if (_availableQuests.Num() == 0)
	{
		return;
	}

	AQuestManager* questManager = GetQuestManager(this);
	if (questManager == nullptr)
	{
		return;
	}

	int randomQuestIndex = UKismetMathLibrary::RandomIntegerInRange(0, _availableQuests.Num()-1);
	questManager->AddActiveQuest(_availableQuests[randomQuestIndex]);
	
	AOfficeZHUD* hud = Cast<AOfficeZHUD>(UGameplayStatics::GetPlayerController(this->GetOwner(), 0)->GetHUD());
	if (hud != nullptr)
	{
		UHudWidget_UI* hudWidget = hud->GetHudWidget();
		if (hudWidget != nullptr)
		{
			hudWidget->ShowBossQuestDialogue(_availableQuests[randomQuestIndex]);
		}
	}

	SetIsPendingQuest(false);

	//_availableQuests.RemoveAt(randomQuestIndex);
}
/*----------------------------------------------------------------------------------------------------*/
bool AOfficeZBoss::IsPendingQuest() const
{
	return _pendingQuest;
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