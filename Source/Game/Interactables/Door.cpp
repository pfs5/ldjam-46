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
void ADoor::InteractWith()
{
	Super::InteractWith();

	if (_boss == nullptr)
	{
		return;
	}

	if (_boss->IsPendingQuest())
	{
		_boss->CreateQuest();
	}
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
