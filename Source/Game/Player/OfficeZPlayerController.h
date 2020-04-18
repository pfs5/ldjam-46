// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OfficeZPlayerController.generated.h"

class AOfficeZPlayer;
class UPaperFlipbook;
class UCharacterMovementComponent;
class ACameraActor;
class UInputWidget;

UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	None,
	Idle,
	Walking,
	Jumping,
	Falling,
	Climbing
};

UENUM(BlueprintType)
enum class EPlayerDirection : uint8
{
	Right,
	Left,
	Back,
	Front
};

UCLASS()
class GAME_API AOfficeZPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;

	virtual void Tick(float deltaSeconds) override;

	virtual void OnPossess(APawn* possesedPawn) override;

	virtual void OnUnPossess() override;

public:
	void SetPlayerState(EPlayerState playerState);

	EPlayerState GetPlayerState() const;

	void OnPlayerStateChanged();

	void SetPlayerDirection(EPlayerDirection playerDirection);

	EPlayerDirection GetPlayerDirection() const;

	void OnPlayerDirectionChanged();

	APawn* GetOwningPlayer() const;

	void Reset();

private:
	UFUNCTION()
	void OnJumpStarted();

	UFUNCTION()
	void OnJumpEnded();

	UFUNCTION()
	void OnJumpApexReached();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

	UFUNCTION()
	void OnLeftButtonPressed();

	UFUNCTION()
	void OnLeftButtonReleased();

	UFUNCTION()
	void OnRightButtonPressed();

	UFUNCTION()
	void OnRightButtonReleased();
	
	void OnXAxis(float axisValue);

	void OnZAxis(float axisValue);

private:
	UPROPERTY(VisibleAnywhere, Category = "Player")
	EPlayerState _playerState;

	UPROPERTY(VisibleAnywhere, Category = "Player")
	EPlayerDirection _playerDirection;

	UPROPERTY(EditAnywhere, Category = "Player")
	UPaperFlipbook* _idleFlipbook;

	UPROPERTY(EditAnywhere, Category = "Player")
	UPaperFlipbook* _walkingFlipbook;

	UPROPERTY(EditAnywhere, Category = "Player")
	UPaperFlipbook* _jumpingFlipbook;

	UPROPERTY(EditAnywhere, Category = "Player")
	UPaperFlipbook* _fallingFlipbook;

	UPROPERTY(EditAnywhere, Category = "Player")
	UPaperFlipbook* _climbingFlipbook;

private:
	UPROPERTY()
	APawn* _owningPlayer;

	UPROPERTY()
	UCharacterMovementComponent* _movementComponent;

	bool _isJumping = false;

	float _movementValue;

	bool _isInGame = false;
	
};
