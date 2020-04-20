// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "CoreMinimal.h"
#include <random>
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
	int32 GetNumActiveQuests() const;

	bool CanAddQuest(UQuest* quest) const;

	void OnActiveQuestCreated();
	void OnActiveQuestRemoved();

	void OnPlayerInteractedWith(AActor* target);
	
	void UpdateQuests(float deltaTime);

	bool ShouldFirePlayer();

	bool IsActorPartOfActiveQuest(const AActor* actor);

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;	

private:
	UPROPERTY()
	TArray<UQuest*> _activeQuests;

	TMap<UQuest*, float> _questTiming;

	UPROPERTY(EditAnywhere, Category="Otkaz")
	float _otkazMeter = 0.0f;

	mutable std::mt19937_64 _randomEngine;
};
/*----------------------------------------------------------------------------------------------------*/
GAME_API AQuestManager* GetQuestManager(const UObject* worldContextObject);
/*----------------------------------------------------------------------------------------------------*/