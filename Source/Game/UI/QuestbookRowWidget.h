// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Styling/SlateBrush.h"
#include "QuestbookRowWidget.generated.h"
/*----------------------------------------------------------------------------------------------------*/
class UTextBlock;
class UQuest;
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class GAME_API UQuestbookRowWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UQuestbookRowWidget(const FObjectInitializer& ObjectInitializer);

	void Init(const UQuest* quest);

	void Update(const UQuest* quest, float time);

	void FinishObjective();

private:
	UPROPERTY(meta = (BindWidget, AllowPrivateAcces = "true"))
	class UTextBlock* _questObjective;

	UPROPERTY(meta = (BindWidget, AllowPrivateAcces = "true"))
	class UTextBlock* _questTimer;

	UPROPERTY(EditAnywhere)
	FSlateBrush _strikeBrush;

	int32 _lastTime;
};
/*----------------------------------------------------------------------------------------------------*/