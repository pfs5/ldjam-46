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

	if (_nextQuestTimer <= 0.0f)
	{
		CreateQuest();

		_nextQuestTimer = UKismetMathLibrary::RandomFloatInRange(_minTimeBetweenQuests, _maxTimeBetweenQuests);
	}
	else
	{
		_nextQuestTimer -= deltaTime;
	}
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

	_availableQuests.RemoveAt(randomQuestIndex);
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