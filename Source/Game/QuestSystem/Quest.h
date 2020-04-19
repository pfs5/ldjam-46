// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Quest.generated.h"
/*----------------------------------------------------------------------------------------------------*/
UENUM()
enum class EObjectiveType : uint8
{
	None,
	Interact,
	Location
};
/*----------------------------------------------------------------------------------------------------*/
USTRUCT()
struct GAME_API FObjectiveData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FText _description;

	UPROPERTY(EditAnywhere)
	EObjectiveType _type;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> _target;
};
/*----------------------------------------------------------------------------------------------------*/
UCLASS(BlueprintType)
class GAME_API UQuest : public UDataAsset
{
	GENERATED_BODY()

public:
	UQuest();

	FText GetName() const;
	FText GetDescription() const;
	float GetDeadline() const;
	FObjectiveData GetObjective() const;

	void SetName(FText name);
	void SetDescription(FText description);
	void SetDeadline(float value);
	void SetObjective(FObjectiveData objectiveData);

private:
	UPROPERTY(EditAnywhere)
	FText _name;

	UPROPERTY(EditAnywhere)
	FText _description;

	// In seconds
	UPROPERTY(EditAnywhere)
	float _deadline;

	UPROPERTY(EditAnywhere)
	FObjectiveData _objective;
};
/*----------------------------------------------------------------------------------------------------*/