// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "InteractableObject.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
/*----------------------------------------------------------------------------------------------------*/
AInteractableObject::AInteractableObject()
{
	PrimaryActorTick.bCanEverTick = false;

	_rootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	_sprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	_sprite->AttachToComponent(_rootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	_collision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	_collision->AttachToComponent(_sprite, FAttachmentTransformRules::KeepRelativeTransform);
	_collision->SetCollisionProfileName("OverlapAll");
}
/*----------------------------------------------------------------------------------------------------*/
/*virtual*/
void AInteractableObject::InteractWith()
{
	if (_interactionFlipbook == nullptr || _idleFlipbook == nullptr)
	{
		return;
	}

	if (_sprite->GetFlipbook() == _interactionFlipbook)
	{
		return;
	}

	_sprite->SetFlipbook(_interactionFlipbook);
	_sprite->SetLooping(false);
}
/*----------------------------------------------------------------------------------------------------*/
void AInteractableObject::BeginPlay()
{
	Super::BeginPlay();
}
/*----------------------------------------------------------------------------------------------------*/
void AInteractableObject::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	Super::EndPlay(endPlayReason);
}
/*----------------------------------------------------------------------------------------------------*/
