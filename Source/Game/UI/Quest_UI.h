// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Quest_UI.generated.h"
/*----------------------------------------------------------------------------------------------------*/
class UTextBlock;
class UQuest;
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class GAME_API UQuest_UI : public UUserWidget
{
	GENERATED_BODY()

public:
	UQuest_UI(const FObjectInitializer& ObjectInitializer);

	void ShowQuest(UQuest* quest);

private:
	UPROPERTY(meta = (BindWidget, AllowPrivateAcces = "true"))
	class UTextBlock* _questDescription;
};
/*----------------------------------------------------------------------------------------------------*/