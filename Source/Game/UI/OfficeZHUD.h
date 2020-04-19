// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "OfficeZHUD.generated.h"
/*----------------------------------------------------------------------------------------------------*/
class UQuest;
class UQuest_UI;
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class GAME_API AOfficeZHUD : public AHUD
{
	GENERATED_BODY()

public:
	AOfficeZHUD();
	
	virtual void DrawHUD() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void ShowBossQuestDialogue(UQuest* quest);
	void HideBossQuestDialogue();

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> _questUIClass;

	UQuest_UI* _questUI;
};
/*----------------------------------------------------------------------------------------------------*/