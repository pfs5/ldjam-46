// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OfficeZGameMode.generated.h"
/*----------------------------------------------------------------------------------------------------*/
class AQuestManager;
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class GAME_API AOfficeZGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AOfficeZGameMode();

	UFUNCTION(BlueprintCallable)
	AQuestManager* GetQuestManager() const;

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category = "Classes")
	TSubclassOf<AQuestManager> _questManagerClass;
	UPROPERTY()
	AQuestManager* _questManager;
};
/*----------------------------------------------------------------------------------------------------*/