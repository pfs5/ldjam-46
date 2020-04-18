// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Quest.generated.h"
/*----------------------------------------------------------------------------------------------------*/
UCLASS(BlueprintType)
class GAME_API UQuest : public UDataAsset
{
	GENERATED_BODY()

public:
	UQuest();

private:
	UPROPERTY(EditAnywhere)
	FText _name;

	UPROPERTY(EditAnywhere)
	FText _description;

	// In seconds
	UPROPERTY(EditAnywhere)
	float _deadline;
};
/*----------------------------------------------------------------------------------------------------*/