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
	Location,
	Dialog
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
	FText GetDialogue() const;
	FObjectiveData GetObjective() const;
	float GetOzkazAddValue() const;
	class UPaperSprite* GetImageSprite() const;

	void SetName(FText name);
	void SetDescription(FText description);
	void SetDeadline(float value);
	void SetDialogue(FText dialogue);
	void SetObjective(FObjectiveData objectiveData);
	void SetOtkazAddValue(float value);

private:
	UPROPERTY(EditAnywhere)
	FText _name;

	UPROPERTY(EditAnywhere)
	FText _description;

	// In seconds
	UPROPERTY(EditAnywhere)
	float _deadline;

	UPROPERTY(EditAnywhere)
	FText _dialogue;

	UPROPERTY(EditAnywhere)
	class UPaperSprite* _image;

	UPROPERTY(EditAnywhere)
	float _otkazAddValue = 0.05;

	UPROPERTY(EditAnywhere)
	FObjectiveData _objective;
};
/*----------------------------------------------------------------------------------------------------*/