// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "InteractableObject.h"
/*----------------------------------------------------------------------------------------------------*/
AInteractableObject::AInteractableObject()
{
	PrimaryActorTick.bCanEverTick = false;
}
/*----------------------------------------------------------------------------------------------------*/
/*virtual*/
void AInteractableObject::InteractWith()
{

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
