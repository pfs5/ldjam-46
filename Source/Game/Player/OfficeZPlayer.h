// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once
/*----------------------------------------------------------------------------------------------------*/
class UPaperSpriteComponent;
class UAudioComponent;
/*----------------------------------------------------------------------------------------------------*/
#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "OfficeZPlayer.generated.h"
/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class GAME_API AOfficeZPlayer : public APaperCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AOfficeZPlayer();

	void ShowThinkingSprite();

	void HideThinkingSprite();

	void SetInteractionsEnabled(bool value);

	bool GetInteractionsEnabled() const;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void UpdateInteractionSpriteVisibility();

private:
	UPROPERTY(EditAnywhere)
	float _pixelsPerUnit = 1.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbookComponent* _thinkingSprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPaperSpriteComponent* _interactionSprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* _audioComponent;

private:
	bool _interactionsEnabled = true;
	bool _isOverlapping = false;
};
/*----------------------------------------------------------------------------------------------------*/