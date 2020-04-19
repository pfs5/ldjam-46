// Fill		out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "OfficeZPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "OfficeZPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "../UI/HudWidget_UI.h"
#include "../UI/OfficeZHUD.h"
/*----------------------------------------------------------------------------------------------------*/
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
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	if (_movementComponent == nullptr || _isInGame == false)
	{
		return;
	}

	float currentAccelerationX = _movementComponent->GetCurrentAcceleration().X;
	float currentAccelerationZ = _movementComponent->GetCurrentAcceleration().Z;

	if (currentAccelerationX != 0.f || currentAccelerationZ != 0)
	{
		SetPlayerState(EPlayerState::Walking);
	}
	else if(currentAccelerationX == 0.f && currentAccelerationZ == 0)
	{
		SetPlayerState(EPlayerState::Idle);
	}
}
/*----------------------------------------------------------------------------------------------------*/
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
/*----------------------------------------------------------------------------------------------------*/
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
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::SetPlayerState(EPlayerState playerState)
{
	if (_playerState == playerState)
	{
		return;
	}

	_playerState = playerState;

	OnPlayerStateChanged();
}
/*----------------------------------------------------------------------------------------------------*/
EPlayerState AOfficeZPlayerController::GetPlayerState() const
{
	return _playerState;
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::OnPlayerStateChanged()
{
	SetFlipbook(_playerState, _playerDirection);
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::SetPlayerDirection(EPlayerDirection playerDirection)
{
	if (_playerDirection == playerDirection)
	{
		return;
	}

	_playerDirection = playerDirection;

	OnPlayerDirectionChanged();
}
/*----------------------------------------------------------------------------------------------------*/
EPlayerDirection AOfficeZPlayerController::GetPlayerDirection() const
{
	return _playerDirection;
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::OnPlayerDirectionChanged()
{
	SetFlipbook(_playerState, _playerDirection);
}
/*----------------------------------------------------------------------------------------------------*/
APawn* AOfficeZPlayerController::GetOwningPlayer() const
{
	return _owningPlayer;
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::Reset()
{
	_playerDirection = EPlayerDirection::Right;
	_owningPlayer->SetActorRotation(FRotator::ZeroRotator);
	SetPlayerState(EPlayerState::Idle);
}
/*----------------------------------------------------------------------------------------------------*/
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
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::OnXAxis(float axisValue)
{
	if (_owningPlayer == nullptr)
	{
		return;
	}

	if (AOfficeZPlayer* player = Cast<AOfficeZPlayer>(_owningPlayer))
	{
		player->AddMovementInput(FVector(1.f, 0.f, 0.f), axisValue);
	}

	if (axisValue > 0)
	{
		SetPlayerDirection(EPlayerDirection::Right);
	}
	else if (axisValue < 0)
	{
		SetPlayerDirection(EPlayerDirection::Left);
	}
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::OnZAxis(float axisValue)
{
	if (_owningPlayer == nullptr)
	{
		return;
	}

	if (AOfficeZPlayer* player = Cast<AOfficeZPlayer>(_owningPlayer))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("Axis value is: %f"), axisValue));
		player->AddMovementInput(FVector(0.f, 0.f, 1.f), axisValue);
	}

	if (axisValue > 0)
	{
		SetPlayerDirection(EPlayerDirection::Back);

	}
	else if (axisValue < 0)
	{
		SetPlayerDirection(EPlayerDirection::Front);
	}
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::SetFlipbook(EPlayerState playerState, EPlayerDirection playerDirection)
{
	AOfficeZPlayer* player = Cast<AOfficeZPlayer>(_owningPlayer);
	if (player == nullptr)
	{
		return;
	}

	UPaperFlipbookComponent* flipbook = player->GetSprite();
	if (flipbook == nullptr)
	{
		return;
	}

	if (playerState == EPlayerState::Idle)
	{
		switch (_playerDirection)
		{
			case EPlayerDirection::Right:
			{
				if (_idleRightFlipbook != nullptr)
				{
					flipbook->SetFlipbook(_idleRightFlipbook);
				}
				break;
			}
			case EPlayerDirection::Left:
			{
				if (_idleLeftFlipbook != nullptr)
				{
					flipbook->SetFlipbook(_idleLeftFlipbook);
				}
				break;
			}
			case EPlayerDirection::Back:
			{
				if (_idleUpFlipbook != nullptr)
				{
					flipbook->SetFlipbook(_idleUpFlipbook);
				}
				break;
			}
			case EPlayerDirection::Front:
			{
				if (_idleDownFlipbook != nullptr)
				{
					flipbook->SetFlipbook(_idleDownFlipbook);
				}
				break;
			}
		}
	}
	else
	{
		switch (_playerDirection)
		{
			case EPlayerDirection::Right:
			{
				if (_walkRightFlipbook != nullptr)
				{
					flipbook->SetFlipbook(_walkRightFlipbook);
				}
				break;
			}
			case EPlayerDirection::Left:
			{
				if (_walkLeftFlipbook != nullptr)
				{
					flipbook->SetFlipbook(_walkLeftFlipbook);
				}
				break;
			}
			case EPlayerDirection::Back:
			{
				if (_walkUpFlipbook != nullptr)
				{
					flipbook->SetFlipbook(_walkUpFlipbook);
				}
				break;
			}
			case EPlayerDirection::Front:
			{
				if (_walkDownFlipbook != nullptr)
				{
					flipbook->SetFlipbook(_walkDownFlipbook);
				}
				break;
			}
		}
	}
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::OpenQuestbook()
{
	AOfficeZHUD* hud = Cast<AOfficeZHUD>(UGameplayStatics::GetPlayerController(this->GetOwner(), 0)->GetHUD());
	if (hud != nullptr)
	{
		UHudWidget_UI* hudWidget = hud->GetHudWidget();
		if (hudWidget != nullptr)
		{
		}
	}
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::CloseQuestbook()
{
	AOfficeZHUD* hud = Cast<AOfficeZHUD>(UGameplayStatics::GetPlayerController(this->GetOwner(), 0)->GetHUD());
	if (hud != nullptr)
	{
		UHudWidget_UI* hudWidget = hud->GetHudWidget();
		if (hudWidget != nullptr)
		{
		}
	}
}
/*----------------------------------------------------------------------------------------------------*/