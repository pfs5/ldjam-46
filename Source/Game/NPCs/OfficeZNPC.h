// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "GameFramework/Actor.h"
#include "../Interactables/NPCDialog.h"
#include "OfficeZNPC.generated.h"
/*----------------------------------------------------------------------------------------------------*/
class UQuest;
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class GAME_API AOfficeZNPC : public ANPCDialog
{
	GENERATED_BODY()

public:
	AOfficeZNPC();

	virtual void StopInteractingWith() override;

	virtual float GetInteractDuration() const override;

private:
	UPROPERTY(EditAnywhere)
	class UPaperFlipbookComponent* FlipbookComponent;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* _overlappBoxComponent;
};
/*----------------------------------------------------------------------------------------------------*/