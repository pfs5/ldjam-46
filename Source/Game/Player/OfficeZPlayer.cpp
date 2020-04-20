// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "OfficeZPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "../Interactables/InteractableObject.h"
/*----------------------------------------------------------------------------------------------------*/
AOfficeZPlayer::AOfficeZPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_thinkingSprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("ThinkingSprite"));
	_thinkingSprite->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	_thinkingSprite->SetHiddenInGame(true);
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (UCapsuleComponent* capsuleComponent = GetCapsuleComponent())
	{
		capsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AOfficeZPlayer::OnOverlapBegin);
	}
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
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayer::ShowThinkingSprite()
{
	_thinkingSprite->SetHiddenInGame(false);
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayer::HideThinkingSprite()
{
	_thinkingSprite->SetHiddenInGame(true);
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZPlayer::OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	if ((otherActor != nullptr) && (otherActor != this) && (otherComp != nullptr))
	{
		if (AInteractableObject* interactableObject = Cast<AInteractableObject>(otherActor))
		{
			interactableObject->Highlight();
		}
	}
}
/*----------------------------------------------------------------------------------------------------*/