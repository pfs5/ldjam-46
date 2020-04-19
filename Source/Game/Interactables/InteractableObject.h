// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.generated.h"
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class GAME_API AInteractableObject : public AActor
{
	GENERATED_BODY()

public:
	AInteractableObject();

	virtual void InteractWith();

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;
};
/*----------------------------------------------------------------------------------------------------*/