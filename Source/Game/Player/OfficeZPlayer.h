// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#pragma once
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

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	float _pixelsPerUnit = 1.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbookComponent* _thinkingSprite;
};
/*----------------------------------------------------------------------------------------------------*/