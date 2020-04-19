// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "CoffeeMachine.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
/*----------------------------------------------------------------------------------------------------*/
ACoffeeMachine::ACoffeeMachine()
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
void ACoffeeMachine::InteractWith()
{
	Super::InteractWith();

	if (_sprite->GetFlipbook() == _filledFlipbook)
	{
		return;
	}

	_sprite->SetFlipbook(_filledFlipbook);
	_sprite->SetLooping(false);
}
/*----------------------------------------------------------------------------------------------------*/
void ACoffeeMachine::BeginPlay()
{
	Super::BeginPlay();
}
/*----------------------------------------------------------------------------------------------------*/
void ACoffeeMachine::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	Super::EndPlay(endPlayReason);
}
/*----------------------------------------------------------------------------------------------------*/
