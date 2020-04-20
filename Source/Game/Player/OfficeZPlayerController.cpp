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
#include <algorithm>
#include "../QuestSystem/QuestManager.h"
#include "../Interactables/InteractableObject.h"
#include "Runtime/Engine/Classes/Engine/World.h"
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent == nullptr)
	{
		return;
	}

	InputComponent->BindAction("Up", EInputEvent::IE_Pressed, this, &AOfficeZPlayerController::InputComponent_OnUpPressed);
	InputComponent->BindAction("Down", EInputEvent::IE_Pressed, this, &AOfficeZPlayerController::InputComponent_OnDownPressed);
	InputComponent->BindAction("Left", EInputEvent::IE_Pressed, this, &AOfficeZPlayerController::InputComponent_OnLeftPressed);
	InputComponent->BindAction("Right", EInputEvent::IE_Pressed, this, &AOfficeZPlayerController::InputComponent_OnRightPressed);

	InputComponent->BindAction("Up", EInputEvent::IE_Released, this, &AOfficeZPlayerController::InputComponent_OnUpReleased);
	InputComponent->BindAction("Down", EInputEvent::IE_Released, this, &AOfficeZPlayerController::InputComponent_OnDownReleased);
	InputComponent->BindAction("Left", EInputEvent::IE_Released, this, &AOfficeZPlayerController::InputComponent_OnLeftReleased);
	InputComponent->BindAction("Right", EInputEvent::IE_Released, this, &AOfficeZPlayerController::InputComponent_OnRightReleased);

	InputComponent->BindAction("ToggleQuestbook", EInputEvent::IE_Pressed, this, &AOfficeZPlayerController::ToggleQuestbook);
	InputComponent->BindAction("Interact", EInputEvent::IE_Pressed, this, &AOfficeZPlayerController::Interact);
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

	MovePlayer();

	//UE_LOG(LogTemp, Warning, TEXT("inputs = %d"), _movementInputs.size());
	//UE_LOG(LogTemp, Warning, TEXT("movement = %s"), *_movementVector.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("dir = %d"), (int)_playerDirection);
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
void AOfficeZPlayerController::InputComponent_OnUpPressed()
{
	_movementUp = 1.f;
	AddMovementInput(EMovementInput::Up);

	UpdateMovementVector();
	UpdateFlipbook();
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::InputComponent_OnDownPressed()
{
	_movementDown = 1.f;
	AddMovementInput(EMovementInput::Down);

	UpdateMovementVector();
	UpdateFlipbook();
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::InputComponent_OnLeftPressed()
{
	_movementLeft = 1.f;
	AddMovementInput(EMovementInput::Left);

	UpdateMovementVector();
	UpdateFlipbook();
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::InputComponent_OnRightPressed()
{
	_movementRight = 1.f;
	AddMovementInput(EMovementInput::Right);

	UpdateMovementVector();
	UpdateFlipbook();
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::InputComponent_OnUpReleased()
{
	_movementUp = 0.f;
	RemoveMovementInput(EMovementInput::Up);

	UpdateMovementVector();
	UpdateFlipbook();
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::InputComponent_OnDownReleased()
{
	_movementDown = 0.f;
	RemoveMovementInput(EMovementInput::Down);

	UpdateMovementVector();
	UpdateFlipbook();
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::InputComponent_OnLeftReleased()
{
	_movementLeft = 0.f;
	RemoveMovementInput(EMovementInput::Left);

	UpdateMovementVector();
	UpdateFlipbook();
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::InputComponent_OnRightReleased()
{
	_movementRight = 0.f;
	RemoveMovementInput(EMovementInput::Right);

	UpdateMovementVector();
	UpdateFlipbook();
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::AddMovementInput(const EMovementInput& input)
{
	RemoveMovementInput(input);
	_movementInputs.push_front(input);
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::RemoveMovementInput(const EMovementInput& input)
{
	_movementInputs.erase(std::remove(_movementInputs.begin(), _movementInputs.end(), input), _movementInputs.end());
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::UpdateMovementVector()
{
	EMovementInput lastInput = _movementInputs.empty() ? EMovementInput::None : _movementInputs.front();

	_movementVector.X = lastInput == EMovementInput::Left || lastInput == EMovementInput::Right ? _movementRight - _movementLeft : 0.f;
	_movementVector.Z = lastInput == EMovementInput::Up || lastInput == EMovementInput::Down ? _movementUp - _movementDown : 0.f;
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::MovePlayer()
{
	if (AOfficeZPlayer* player = Cast<AOfficeZPlayer>(_owningPlayer))
	{
		player->AddMovementInput(_movementVector);
	}
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::UpdateFlipbook()
{
	// Get player direction
	EMovementInput lastMovementInput = _movementInputs.empty() ? EMovementInput::None : _movementInputs.front();
	if (lastMovementInput == EMovementInput::None)
	{
		return;
	}

	switch (lastMovementInput)
	{
		case EMovementInput::Up:
		{
			SetPlayerDirection(EPlayerDirection::Back);
			break;
		}
		case EMovementInput::Down:
		{
			SetPlayerDirection(EPlayerDirection::Front);
			break;
		}
		case EMovementInput::Left:
		{
			SetPlayerDirection(EPlayerDirection::Left);
			break;
		}
		case EMovementInput::Right:
		{
			SetPlayerDirection(EPlayerDirection::Right);
			break;
		}
	}
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::OnInteractFinished()
{
	UnfreezePlayer();
	if (AOfficeZPlayer* player = Cast<AOfficeZPlayer>(_owningPlayer))
	{
		player->HideThinkingSprite();
	}

	GetWorldTimerManager().ClearTimer(_interactionDurationTimerHandle);
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::FreezePlayer()
{
	_movementInputs.clear();
	_movementUp = 0.f;
	_movementDown = 0.f;
	_movementLeft = 0.f;
	_movementRight = 0.f;

	UpdateMovementVector();

	DisableInput(this);
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::UnfreezePlayer()
{
	EnableInput(this);
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
void AOfficeZPlayerController::ToggleQuestbook()
{
	AOfficeZHUD* hud = Cast<AOfficeZHUD>(GetHUD());
	if (hud != nullptr)
	{
		UHudWidget_UI* hudWidget = hud->GetHudWidget();
		if (hudWidget != nullptr)
		{
			hudWidget->ToggleQuestbook();
		}
	}
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::Interact()
{
	AQuestManager* questManager = GetQuestManager(this);
	if (questManager == nullptr)
	{
		return;
	}

	TArray<AActor*> overlappingActors;
	if (AOfficeZPlayer* player = Cast<AOfficeZPlayer>(_owningPlayer))
	{
		if (UCapsuleComponent* capsuleComponent = player->GetCapsuleComponent())
		{
			capsuleComponent->GetOverlappingActors(overlappingActors);

			for (int i = 0; i < overlappingActors.Num(); ++i)
			{
				if (AInteractableObject* interactableObject = Cast<AInteractableObject>(overlappingActors[i]))
				{
					if (interactableObject->InteractWith())
					{
						FreezePlayer();
						player->ShowThinkingSprite();
						GetWorldTimerManager().SetTimer(_interactionDurationTimerHandle, this, &AOfficeZPlayerController::OnInteractFinished, _interactionDuration);

						questManager->OnPlayerInteractedWith(overlappingActors[i]);
					}
				}

				//GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, *overlappingActors[i]->GetName());
			}
		}
	}
}
/*----------------------------------------------------------------------------------------------------*/