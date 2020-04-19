// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "Printer.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
/*----------------------------------------------------------------------------------------------------*/
APrinter::APrinter()
{
	PrimaryActorTick.bCanEverTick = false;

	_rootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	_sprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	_sprite->AttachToComponent(_rootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	_collision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	_collision->AttachToComponent(_sprite, FAttachmentTransformRules::KeepRelativeTransform);
}
/*----------------------------------------------------------------------------------------------------*/
/*override*/
void APrinter::InteractWith()
{
	Super::InteractWith();

	if (_sprite->GetFlipbook() == _idleFlipbook)
	{
		return;
	}

	_sprite->SetFlipbook(_printingFlipbook);
	_sprite->SetLooping(false);
}
/*----------------------------------------------------------------------------------------------------*/
void APrinter::BeginPlay()
{
	Super::BeginPlay();
}
/*----------------------------------------------------------------------------------------------------*/
void APrinter::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	Super::EndPlay(endPlayReason);
}
/*----------------------------------------------------------------------------------------------------*/
