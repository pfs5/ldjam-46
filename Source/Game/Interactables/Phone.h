// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "Phone.generated.h"
/*----------------------------------------------------------------------------------------------------*/
class UBoxComponent;
class UPaperFlipbook;
class UPaperFlipbookComponent;
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class GAME_API APhone : public AInteractableObject
{
	GENERATED_BODY()

public:
	APhone();

	virtual bool InteractWith() override;

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;
};
/*----------------------------------------------------------------------------------------------------*/