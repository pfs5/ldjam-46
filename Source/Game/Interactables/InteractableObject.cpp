// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "InteractableObject.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
/*----------------------------------------------------------------------------------------------------*/
AInteractableObject::AInteractableObject()
{
	PrimaryActorTick.bCanEverTick = false;

	_baznaRootKomponenta = CreateDefaultSubobject<USceneComponent>(TEXT("BaznaRutnaKomponenta"));
	this->RootComponent = _baznaRootKomponenta;


	_sprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	_sprite->AttachToComponent(_baznaRootKomponenta, FAttachmentTransformRules::KeepRelativeTransform);

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

	SetIsBeingInteractedWith(true);

	UpdateFlipBook();

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

	_isHighlighted = true;
	UpdateFlipBook();
}
/*----------------------------------------------------------------------------------------------------*/
void AInteractableObject::RemoveHighlight()
{
	if (_idleFlipbook == nullptr)
	{
		return;
	}

	_isHighlighted = false;
	UpdateFlipBook();
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

	UpdateFlipBook();
}
/*----------------------------------------------------------------------------------------------------*/
void AInteractableObject::UpdateFlipBook()
{
	if (_isBeingInteractedWith)
	{
		_sprite->SetFlipbook(_interactionFlipbook);
		_sprite->SetLooping(false);
		_sprite->PlayFromStart();
	}
	else
	{
		_sprite->SetFlipbook(_isHighlighted ? _highlightedFlipbook : _idleFlipbook);
	}
}
/*----------------------------------------------------------------------------------------------------*/
float AInteractableObject::GetInteractDuration() const
{
	return _interactDuration;
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
