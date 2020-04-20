// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "Printer.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
/*----------------------------------------------------------------------------------------------------*/
APrinter::APrinter()
{
	PrimaryActorTick.bCanEverTick = false;
}
/*----------------------------------------------------------------------------------------------------*/
/*override*/
bool APrinter::InteractWith()
{
	return Super::InteractWith();
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
