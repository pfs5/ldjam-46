// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "OfficeZBoss.generated.h"
/*----------------------------------------------------------------------------------------------------*/
class UQuest;
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class GAME_API AOfficeZBoss : public APaperCharacter
{
	GENERATED_BODY()

public:
	AOfficeZBoss();

	virtual void Tick(float DeltaTime) override;

	void CreateQuest();

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;

private:
	void OnQuestCreated();

private:
	UPROPERTY(EditAnywhere)
	TArray<UQuest*> _availableQuests;

	UPROPERTY(EditAnywhere)
	float _minTimeBetweenQuests = 30.0f;

	UPROPERTY(EditAnywhere)
	float _maxTimeBetweenQuests = 60.0f;

	float _nextQuestTimer = 0.0f;
};
/*----------------------------------------------------------------------------------------------------*/