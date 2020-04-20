// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.generated.h"
/*----------------------------------------------------------------------------------------------------*/
class UBoxComponent;
class UPaperFlipbook;
class UPaperFlipbookComponent;
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class GAME_API AInteractableObject : public AActor
{
	GENERATED_BODY()

public:
	AInteractableObject();

	virtual bool InteractWith();

	virtual void StopInteractingWith();

	void Highlight();

	bool IsBeingInteractedWith() const;

	void SetIsBeingInteractedWith(bool value);

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* _rootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbookComponent* _sprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* _collision;

	UPROPERTY(EditAnywhere, Category = "Flipbook")
	UPaperFlipbook* _interactionFlipbook;

	UPROPERTY(EditAnywhere, Category = "Flipbook")
	UPaperFlipbook* _idleFlipbook;

	UPROPERTY(EditAnywhere, Category = "Flipbook")
	UPaperFlipbook* _highlightedFlipbook;

	bool _isBeingInteractedWith = false;
};
/*----------------------------------------------------------------------------------------------------*/