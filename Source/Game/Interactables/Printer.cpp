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
	_sprite->AttachTo(_rootComponent);

	_collision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	_collision->AttachTo(_sprite);
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
