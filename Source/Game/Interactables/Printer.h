// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "Printer.generated.h"
/*----------------------------------------------------------------------------------------------------*/
class AOfficeZBoss;
class UBoxComponent;
class UPaperFlipbook;
class UPaperFlipbookComponent;
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class GAME_API APrinter : public AInteractableObject
{
	GENERATED_BODY()

public:
	APrinter();

	virtual void InteractWith() override;

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* _rootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbookComponent* _sprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* _collision;

	UPROPERTY(EditAnywhere, Category = "Flipbook")
	UPaperFlipbook* _idleFlipbook;

	UPROPERTY(EditAnywhere, Category = "Flipbook")
	UPaperFlipbook* _printingFlipbook;
};
/*----------------------------------------------------------------------------------------------------*/