// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "Door.h"
#include "../NPCs/OfficeZBoss.h"
#include "PaperSpriteComponent.h"
/*----------------------------------------------------------------------------------------------------*/
ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = false;

	_openDoorImage = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("OpenDoorImage"));
	_openDoorImage->AttachToComponent(_rootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}
/*----------------------------------------------------------------------------------------------------*/
/*override*/
bool ADoor::InteractWith()
{
	Super::InteractWith();

	_interactionDuration = Super::GetInteractDuration();

	if (_boss == nullptr)
	{
		return false;
	}

	if (_boss->IsPendingQuest())
	{
		if (_openDoorImage != nullptr)
		{
			_openDoorImage->SetHiddenInGame(false);
		}

		_boss->SetActorLocation(_screamingBossLocation);
		_boss->CreateQuest();

		_interactionDuration = 3.f;

		return true;
	}

	return true;
}
/*----------------------------------------------------------------------------------------------------*/
float ADoor::GetInteractDuration() const
{
	return _interactionDuration;
}
/*----------------------------------------------------------------------------------------------------*/
void ADoor::HideOpenDoor()
{
	if (_openDoorImage != nullptr)
	{
		_openDoorImage->SetHiddenInGame(true);
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
