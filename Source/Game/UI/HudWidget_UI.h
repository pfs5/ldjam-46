// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HudWidget_UI.generated.h"
/*----------------------------------------------------------------------------------------------------*/
class UTextBlock;
class UQuest;
class UQuest_UI;
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class GAME_API UHudWidget_UI : public UUserWidget
{
	GENERATED_BODY()

public:
	UHudWidget_UI(const FObjectInitializer& ObjectInitializer);

	UQuest_UI* GetQuestUI() const;

private:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UQuest_UI* _questUI;
};
/*----------------------------------------------------------------------------------------------------*/