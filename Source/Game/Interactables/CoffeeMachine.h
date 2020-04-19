// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "CoffeeMachine.generated.h"
/*----------------------------------------------------------------------------------------------------*/
class AOfficeZBoss;
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class GAME_API ACoffeeMachine : public AInteractableObject
{
	GENERATED_BODY()

public:
	ACoffeeMachine();

	virtual void InteractWith() override;

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;
};
/*----------------------------------------------------------------------------------------------------*/