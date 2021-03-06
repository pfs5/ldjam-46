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
#include "../UI/QuestbookWidget.h"
#include "../QuestSystem/Quest.h"
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

	InputComponent->BindAction("ScrollUp", EInputEvent::IE_Pressed, this, &AOfficeZPlayerController::InputComponent_OnScrollUp);
	InputComponent->BindAction("ScrollDown", EInputEvent::IE_Pressed, this, &AOfficeZPlayerController::InputComponent_OnScrollDown);
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

		FreezePlayer();
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
	_playerDirection = EPlayerDirection::Left;
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
	if (!_interactionsEnabled)
	{
		return;
	}

	_movementUp = 1.f;
	AddMovementInput(EMovementInput::Up);

	UpdateMovementVector();
	UpdateFlipbook();
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::InputComponent_OnDownPressed()
{
	if (!_interactionsEnabled)
	{
		return;
	}

	_movementDown = 1.f;
	AddMovementInput(EMovementInput::Down);

	UpdateMovementVector();
	UpdateFlipbook();
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::InputComponent_OnLeftPressed()
{
	if (!_interactionsEnabled)
	{
		return;
	}

	_movementLeft = 1.f;
	AddMovementInput(EMovementInput::Left);

	UpdateMovementVector();
	UpdateFlipbook();
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::InputComponent_OnRightPressed()
{
	if (!_interactionsEnabled)
	{
		return;
	}

	_movementRight = 1.f;
	AddMovementInput(EMovementInput::Right);

	UpdateMovementVector();
	UpdateFlipbook();
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::InputComponent_OnUpReleased()
{
	if (!_interactionsEnabled)
	{
		return;
	}

	_movementUp = 0.f;
	RemoveMovementInput(EMovementInput::Up);

	UpdateMovementVector();
	UpdateFlipbook();
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::InputComponent_OnDownReleased()
{
	if (!_interactionsEnabled)
	{
		return;
	}

	_movementDown = 0.f;
	RemoveMovementInput(EMovementInput::Down);

	UpdateMovementVector();
	UpdateFlipbook();
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::InputComponent_OnLeftReleased()
{
	if (!_interactionsEnabled)
	{
		return;
	}

	_movementLeft = 0.f;
	RemoveMovementInput(EMovementInput::Left);

	UpdateMovementVector();
	UpdateFlipbook();
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::InputComponent_OnRightReleased()
{
	if (!_interactionsEnabled)
	{
		return;
	}

	_movementRight = 0.f;
	RemoveMovementInput(EMovementInput::Right);

	UpdateMovementVector();
	UpdateFlipbook();
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::InputComponent_OnScrollUp()
{
	if (!_isQuestbookOpened)
	{
		return;
	}

	AOfficeZHUD* hud = Cast<AOfficeZHUD>(GetHUD());
	if (hud != nullptr)
	{
		UHudWidget_UI* hudWidget = hud->GetHudWidget();
		if (hudWidget != nullptr)
		{
			UQuestbookWidget* questbookWidget = hudWidget->GetQuestbookWidget();
			if (questbookWidget != nullptr)
			{
				questbookWidget->ScrollMoveUp();
			}
		}
	}
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::InputComponent_OnScrollDown()
{
	if (!_isQuestbookOpened)
	{
		return;
	}

	AOfficeZHUD* hud = Cast<AOfficeZHUD>(GetHUD());
	if (hud != nullptr)
	{
		UHudWidget_UI* hudWidget = hud->GetHudWidget();
		if (hudWidget != nullptr)
		{
			UQuestbookWidget* questbookWidget = hudWidget->GetQuestbookWidget();
			if (questbookWidget != nullptr)
			{
				questbookWidget->ScrollMoveDown();
			}
		}
	}
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

	_currentInteractable->StopInteractingWith();
	SetCurrentInteractable(nullptr);

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

	_interactionsEnabled = false;

	if (AOfficeZPlayer* player = Cast<AOfficeZPlayer>(GetPawn()))
	{
		player->SetInteractionsEnabled(false);
	}
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::UnfreezePlayer()
{
	_interactionsEnabled = true;

	if (AOfficeZPlayer* player = Cast<AOfficeZPlayer>(GetPawn()))
	{
		player->SetInteractionsEnabled(true);
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
void AOfficeZPlayerController::ToggleQuestbook()
{
	if (!_interactionsEnabled)
	{
		return;
	}

	AOfficeZHUD* hud = Cast<AOfficeZHUD>(GetHUD());
	if (hud != nullptr)
	{
		UHudWidget_UI* hudWidget = hud->GetHudWidget();
		if (hudWidget != nullptr)
		{
			hudWidget->ToggleQuestbook();
			_isQuestbookOpened = !_isQuestbookOpened;
		}
	}
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::Interact()
{
	if (!_gameStarted)
	{
		StartGame();
	}

	if (_gameOver)
	{
		UGameplayStatics::OpenLevel(this, TEXT("TestLevel_Patrik"));
		return;
	}

	AQuestManager* questManager = GetQuestManager(this);
	if (questManager == nullptr)
	{
		return;
	}

	if (!_interactionsEnabled)
	{
		AOfficeZPlayerController::OnInteractFinished();
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
						SetCurrentInteractable(interactableObject);

						float duration = interactableObject->GetInteractDuration();
						if (duration < KINDA_SMALL_NUMBER)
						{
							AOfficeZPlayerController::OnInteractFinished();
						}
						else
						{
							GetWorldTimerManager().SetTimer(_interactionDurationTimerHandle, this, &AOfficeZPlayerController::OnInteractFinished, interactableObject->GetInteractDuration());
						}

						questManager->OnPlayerInteractedWith(overlappingActors[i]);
					}
				}

				//GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, *overlappingActors[i]->GetName());
			}
		}
	}
}
/*----------------------------------------------------------------------------------------------------*/
AInteractableObject* AOfficeZPlayerController::GetCurrentInteractable()
{
	return _currentInteractable;
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayerController::SetCurrentInteractable(AInteractableObject* currentInteractable)
{
	if (_currentInteractable == currentInteractable)
	{
		return;
	}

	_currentInteractable = currentInteractable;
}
//--------------------------------------------------------------------------------------------------
void AOfficeZPlayerController::StartGame()
{
	_gameStarted = true;

	AOfficeZHUD* hud = Cast<AOfficeZHUD>(GetHUD());
	if (hud != nullptr)
	{
		UHudWidget_UI* hudWidget = hud->GetHudWidget();
		if (hudWidget != nullptr)
		{
			hudWidget->StartGame();
		}
	}

	UnfreezePlayer();

	ShowTutorial();
}
//--------------------------------------------------------------------------------------------------
void AOfficeZPlayerController::FinishGame()
{
	FreezePlayer();

	_gameOver = true;
}
//--------------------------------------------------------------------------------------------------
bool AOfficeZPlayerController::IsGameStarted()
{
	return _gameStarted;
}
//--------------------------------------------------------------------------------------------------
bool AOfficeZPlayerController::IsTutorialDone()
{
	return _tutorialDone;
}
//--------------------------------------------------------------------------------------------------
void AOfficeZPlayerController::ShowTutorial()
{
	if(_tutorialQuest == nullptr)
	{
		return;
	}

	AOfficeZHUD* hud = Cast<AOfficeZHUD>(GetHUD());
	if (hud != nullptr)
	{
		UHudWidget_UI* hudWidget = hud->GetHudWidget();
		if (hudWidget != nullptr)
		{
			hudWidget->ShowBossQuestDialogue(_tutorialQuest, true);
		}
	}

	_tutorialDone = true;
}
/*----------------------------------------------------------------------------------------------------*/