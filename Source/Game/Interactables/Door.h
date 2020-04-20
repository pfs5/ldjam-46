// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "Door.generated.h"
/*----------------------------------------------------------------------------------------------------*/
class AOfficeZBoss;
class UPaperSpriteComponent;
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class GAME_API ADoor : public AInteractableObject
{
	GENERATED_BODY()

public:
	ADoor();

	virtual bool InteractWith() override;

	virtual float GetInteractDuration() const override;

	void HideOpenDoor();

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;

private:
	UPROPERTY(EditAnywhere)
	AOfficeZBoss* _boss;

	UPROPERTY(EditAnywhere)
	FVector _screamingBossLocation;

	UPROPERTY(EditAnywhere)
	UPaperSpriteComponent* _openDoorImage;

	float _interactionDuration;
};
/*----------------------------------------------------------------------------------------------------*/