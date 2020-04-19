// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "OfficeZHUD.generated.h"
/*----------------------------------------------------------------------------------------------------*/
class UQuest;
class UHudWidget_UI;
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

	UHudWidget_UI* GetHudWidget() const;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> _hudWidgetClass;
	
	UHudWidget_UI* _hudWidget;

	UPROPERTY(EditAnywhere)
	float _dialogueOnScreenTime = 5.0f;

	float _dialogueOnScreenTimer = 0.0f;
};
/*----------------------------------------------------------------------------------------------------*/