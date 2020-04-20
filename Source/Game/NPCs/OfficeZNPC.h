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

private:
	UPROPERTY(EditAnywhere)
	class UPaperFlipbookComponent* FlipbookComponent;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere)
	class UPaperSpriteComponent* SpriteComponent;

};
/*----------------------------------------------------------------------------------------------------*/