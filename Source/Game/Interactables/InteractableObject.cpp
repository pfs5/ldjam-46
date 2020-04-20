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
bool AInteractableObject::InteractWith()
{
	if (_interactionFlipbook == nullptr || _idleFlipbook == nullptr)
	{
		return false;
	}

	if (_sprite->GetFlipbook() == _interactionFlipbook)
	{
		return false;
	}

	_sprite->SetFlipbook(_interactionFlipbook);
	//_sprite->SetLooping(false);

	SetIsBeingInteractedWith(true);

	return true;
}
/*----------------------------------------------------------------------------------------------------*/
/*virtual*/
void AInteractableObject::StopInteractingWith()
{
	SetIsBeingInteractedWith(false);
}
/*----------------------------------------------------------------------------------------------------*/
void AInteractableObject::Highlight()
{
	if (_isBeingInteractedWith)
	{
		return;
	}

	if (_highlightedFlipbook == nullptr)
	{
		return;
	}

	_sprite->SetFlipbook(_highlightedFlipbook);
}
/*----------------------------------------------------------------------------------------------------*/
void AInteractableObject::RemoveHighlight()
{
	if (_idleFlipbook == nullptr)
	{
		return;
	}

	_sprite->SetFlipbook(_idleFlipbook);
}
/*----------------------------------------------------------------------------------------------------*/
bool AInteractableObject::IsBeingInteractedWith() const
{
	return _isBeingInteractedWith;
}
/*----------------------------------------------------------------------------------------------------*/
void AInteractableObject::SetIsBeingInteractedWith(bool isBeingInteractedWith)
{
	if (_isBeingInteractedWith == isBeingInteractedWith)
	{
		return;
	}

	_isBeingInteractedWith = isBeingInteractedWith;
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
