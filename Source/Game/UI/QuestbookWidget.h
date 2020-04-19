// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestbookWidget.generated.h"
/*----------------------------------------------------------------------------------------------------*/
class UQuest;
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class GAME_API UQuestbookWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UQuestbookWidget(const FObjectInitializer& ObjectInitializer);

	void AddActiveQuest(UQuest* quest);
	void RemoveActiveQuest(UQuest* quest);
};
/*----------------------------------------------------------------------------------------------------*/