// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "WaterMachine.generated.h"
/*----------------------------------------------------------------------------------------------------*/
class AOfficeZBoss;
class UBoxComponent;
class UPaperFlipbook;
class UPaperFlipbookComponent;
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class GAME_API AWaterMachine : public AInteractableObject
{
	GENERATED_BODY()

public:
	AWaterMachine();

	virtual void InteractWith() override;

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;
};
/*----------------------------------------------------------------------------------------------------*/