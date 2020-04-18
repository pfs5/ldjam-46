// Fill		out your copyright notice in the Description page of Project Settings.

#include "OfficeZPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "OfficeZPlayer.h"

void AOfficeZPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent == nullptr)
	{
		return;
	}

	InputComponent->BindAxis("XAxis", this, &AOfficeZPlayerController::OnXAxis);
	InputComponent->BindAxis("ZAxis", this, &AOfficeZPlayerController::OnZAxis);
}

void AOfficeZPlayerController::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	if (_movementComponent == nullptr || _isInGame == false)
	{
		return;
	}

	if (_movementValue > 0.f)
	{
		OnXAxis(1.f);
	}
	else if (_movementValue < 0.f)
	{
		OnXAxis(-1.f);
	}
	else if(_movementValue == 0.0f)
	{
		OnXAxis(0.f);
	}

	float currentAcceleration = _movementComponent->GetCurrentAcceleration().X;

	if (currentAcceleration != 0.f)
	{
		SetPlayerState(EPlayerState::Walking);
	}
	else
	{
		SetPlayerState(EPlayerState::Idle);
	}

	// DIRECTION
	if (currentAcceleration > 0)
	{
		SetPlayerDirection(EPlayerDirection::Right);
		
	}
	else if (currentAcceleration < 0)
	{
		SetPlayerDirection(EPlayerDirection::Left);
	}
}

void AOfficeZPlayerController::OnPossess(APawn* possesedPawn)
{
	Super::OnPossess(possesedPawn);

	if (possesedPawn != nullptr)
	{
		_owningPlayer = possesedPawn;

		_movementComponent = Cast<UCharacterMovementComponent>(_owningPlayer->GetMovementComponent());

		if (AOfficeZPlayer* player = Cast<AOfficeZPlayer>(_owningPlayer))
		{			
			if (UCapsuleComponent* capsuleComponent = player->GetCapsuleComponent())
			{
				capsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AOfficeZPlayerController::OnOverlapBegin);
			}
		}

		Reset();
		
		_isInGame = true;
	}
}

void AOfficeZPlayerController::OnUnPossess()
{
	Super::OnUnPossess();

	_isInGame = false;

	SetPlayerState(EPlayerState::None);

	if (AOfficeZPlayer* player = Cast<AOfficeZPlayer>(_owningPlayer))
	{
		if (UCapsuleComponent* capsuleComponent = player->GetCapsuleComponent())
		{
			capsuleComponent->OnComponentBeginOverlap.RemoveDynamic(this, &AOfficeZPlayerController::OnOverlapBegin);
		}
	}
}

void AOfficeZPlayerController::SetPlayerState(EPlayerState playerState)
{
	if (_playerState == playerState)
	{
		return;
	}

	_playerState = playerState;

	OnPlayerStateChanged();
}

EPlayerState AOfficeZPlayerController::GetPlayerState() const
{
	return _playerState;
}

void AOfficeZPlayerController::OnPlayerStateChanged()
{
	AOfficeZPlayer* player = Cast<AOfficeZPlayer>(_owningPlayer);
	if(player == nullptr)
	{
		return;
	}

	UPaperFlipbookComponent* flipbook = player->GetSprite();
	if (flipbook == nullptr)
	{
		return;
	}

	switch (_playerState)
	{
		case EPlayerState::Idle:
		{
			if (_idleFlipbook != nullptr)
			{
				flipbook->SetFlipbook(_idleFlipbook);
			}

			break;
		}
		case EPlayerState::Walking:
		{
			if (_walkingFlipbook != nullptr)
			{
				flipbook->SetFlipbook(_walkingFlipbook);
			}

			break;
		}
	}
}

void AOfficeZPlayerController::SetPlayerDirection(EPlayerDirection playerDirection)
{
	if (_playerDirection == playerDirection)
	{
		return;
	}

	_playerDirection = playerDirection;

	OnPlayerDirectionChanged();
}

EPlayerDirection AOfficeZPlayerController::GetPlayerDirection() const
{
	return _playerDirection;
}

void AOfficeZPlayerController::OnPlayerDirectionChanged()
{
	AOfficeZPlayer* player = Cast<AOfficeZPlayer>(_owningPlayer);
	if (player == nullptr)
	{
		return;
	}

	switch (_playerDirection)
	{
		case EPlayerDirection::Right:
		{
			player->FlipSprite();

			break;
		}
		case EPlayerDirection::Left:
		{
			player->FlipSprite();

			break;
		}
		case EPlayerDirection::Back:
		{

			break;
		}
		case EPlayerDirection::Front:
		{

			break;
		}
	}
}

APawn* AOfficeZPlayerController::GetOwningPlayer() const
{
	return _owningPlayer;
}

void AOfficeZPlayerController::Reset()
{
	_playerDirection = EPlayerDirection::Right;
	_owningPlayer->SetActorRotation(FRotator::ZeroRotator);
	SetPlayerState(EPlayerState::Idle);
}

void AOfficeZPlayerController::OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	if (otherActor == nullptr && otherActor == this && otherComp == nullptr)
	{
		return;
	}

	//if (otherComp->ComponentHasTag("Portal"))
	//{
	//	if (AOfficeZPlayer* player = Cast<AOfficeZPlayer>(_owningPlayer))
	//	{
	//		player->OnReachedJumpApex.RemoveDynamic(this, &AOfficeZPlayerController::OnJumpApexReached);
	//		player->Destroy();
	//	}
	//}
}

void AOfficeZPlayerController::OnXAxis(float axisValue)
{
	if (_owningPlayer == nullptr)
	{
		return;
	}

	if (AOfficeZPlayer* player = Cast<AOfficeZPlayer>(_owningPlayer))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("Axis value is: %f"), axisValue));

		player->AddMovementInput(FVector(1.f, 0.f, 0.f), axisValue);
	}
}

void AOfficeZPlayerController::OnZAxis(float axisValue)
{
	if (_owningPlayer == nullptr)
	{
		return;
	}

	if (AOfficeZPlayer* player = Cast<AOfficeZPlayer>(_owningPlayer))
	{
		player->AddMovementInput(FVector(0.f, 0.f, 1.f), axisValue);
	}
}
