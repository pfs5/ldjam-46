// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "OfficeZPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "../Interactables/InteractableObject.h"
#include "PaperSpriteComponent.h"
#include "Components/AudioComponent.h"
/*----------------------------------------------------------------------------------------------------*/
AOfficeZPlayer::AOfficeZPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_thinkingSprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("ThinkingSprite"));
	_thinkingSprite->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	_thinkingSprite->SetHiddenInGame(true);

	_interactionSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("InteractionSprite"));
	_interactionSprite->SetupAttachment(RootComponent);

	_audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	_audioComponent->SetupAttachment(RootComponent);
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (UCapsuleComponent* capsuleComponent = GetCapsuleComponent())
	{
		capsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AOfficeZPlayer::OnOverlapBegin);
		capsuleComponent->OnComponentEndOverlap.AddDynamic(this, &AOfficeZPlayer::OnOverlapEnd);
	}

	_interactionSprite->SetHiddenInGame(true);
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayer::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	Super::EndPlay(endPlayReason);
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayer::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	const float unitsPerPixel = 1.f / _pixelsPerUnit;

	FVector location = GetActorLocation();
	location.X = FMath::GridSnap(location.X, unitsPerPixel);
	location.Z = FMath::GridSnap(location.Z, unitsPerPixel);
	SetActorLocation(location);

	if (UCharacterMovementComponent* movement = Cast<UCharacterMovementComponent>(GetMovementComponent()))
	{
		FVector a = movement->GetCurrentAcceleration();
		_audioComponent->SetVolumeMultiplier(a.IsNearlyZero() ? 0.f : 1.f);
	}
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayer::UpdateInteractionSpriteVisibility()
{
	_interactionSprite->SetHiddenInGame(!(_isOverlapping && _interactionsEnabled));
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayer::ShowThinkingSprite()
{
	_thinkingSprite->SetHiddenInGame(false);
	_thinkingSprite->PlayFromStart();
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayer::HideThinkingSprite()
{
	_thinkingSprite->SetHiddenInGame(true);
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayer::SetInteractionsEnabled(bool value)
{
	_interactionsEnabled = value;

	UpdateInteractionSpriteVisibility();
}
/*----------------------------------------------------------------------------------------------------*/
bool AOfficeZPlayer::GetInteractionsEnabled() const
{
	return _interactionsEnabled;
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayer::OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	if ((otherActor != nullptr) && (otherActor != this) && (otherComp != nullptr))
	{
		if (AInteractableObject* interactableObject = Cast<AInteractableObject>(otherActor))
		{
			_isOverlapping = true;
			interactableObject->Highlight();
			UpdateInteractionSpriteVisibility();
		}
	}
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayer::OnOverlapEnd(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex)
{
	if ((otherActor != nullptr) && (otherActor != this) && (otherComp != nullptr))
	{
		if (AInteractableObject* interactableObject = Cast<AInteractableObject>(otherActor))
		{
			_isOverlapping = false;
			interactableObject->RemoveHighlight();
		}
	}

	UpdateInteractionSpriteVisibility();
}
/*----------------------------------------------------------------------------------------------------*/