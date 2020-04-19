// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "CoreMinimal.h"
#include "QuestManager.generated.h"
/*----------------------------------------------------------------------------------------------------*/
class UQuest;
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class GAME_API AQuestManager : public AActor
{
	GENERATED_BODY()

public:
	AQuestManager();

	virtual void Tick(float DeltaTime) override;

	void AddActiveQuest(UQuest* quest);
	void RemoveActiveQuest(UQuest* quest);

	void OnActiveQuestCreated();
	void OnActiveQuestRemoved();

	void UpdateQuests(float deltaTime);

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;	

private:
	UPROPERTY()
	TArray<UQuest*> _currentQuests;
};
/*----------------------------------------------------------------------------------------------------*/
GAME_API AQuestManager* GetQuestManager(const UObject* worldContextObject);
/*----------------------------------------------------------------------------------------------------*/