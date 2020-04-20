// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "Door.h"
#include "../NPCs/OfficeZBoss.h"
/*----------------------------------------------------------------------------------------------------*/
ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = false;
}
/*----------------------------------------------------------------------------------------------------*/
/*override*/
bool ADoor::InteractWith()
{
	Super::InteractWith();

	if (_boss == nullptr)
	{
		return false;
	}

	if (_boss->IsPendingQuest())
	{
		_boss->SetActorLocation(_screamingBossLocation);
		_boss->CreateQuest();

		return true;
	}

	return false;
}
/*----------------------------------------------------------------------------------------------------*/
void ADoor::BeginPlay()
{
	Super::BeginPlay();
}
/*----------------------------------------------------------------------------------------------------*/
void ADoor::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	Super::EndPlay(endPlayReason);
}
/*----------------------------------------------------------------------------------------------------*/
