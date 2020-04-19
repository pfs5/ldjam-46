// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "WaterMachine.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
/*----------------------------------------------------------------------------------------------------*/
AWaterMachine::AWaterMachine()
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
void AWaterMachine::InteractWith()
{
	Super::InteractWith();
}
/*----------------------------------------------------------------------------------------------------*/
void AWaterMachine::BeginPlay()
{
	Super::BeginPlay();
}
/*----------------------------------------------------------------------------------------------------*/
void AWaterMachine::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	Super::EndPlay(endPlayReason);
}
/*----------------------------------------------------------------------------------------------------*/
