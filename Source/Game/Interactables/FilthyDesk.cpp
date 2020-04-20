// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "FilthyDesk.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
/*----------------------------------------------------------------------------------------------------*/
AFilthyDesk::AFilthyDesk()
{
	PrimaryActorTick.bCanEverTick = false;
}
/*----------------------------------------------------------------------------------------------------*/
/*override*/
bool AFilthyDesk::InteractWith()
{
	return Super::InteractWith();
}
/*----------------------------------------------------------------------------------------------------*/
void AFilthyDesk::BeginPlay()
{
	Super::BeginPlay();
}
/*----------------------------------------------------------------------------------------------------*/
void AFilthyDesk::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	Super::EndPlay(endPlayReason);
}
/*----------------------------------------------------------------------------------------------------*/
