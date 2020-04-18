// Fill out your copyright notice in the Description page of Project Settings.


#include "OfficeZPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AOfficeZPlayer::AOfficeZPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AOfficeZPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void AOfficeZPlayer::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	Super::EndPlay(endPlayReason);
}

// Called every frame
void AOfficeZPlayer::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void AOfficeZPlayer::Landed(const FHitResult& hit)
{
	Super::Landed(hit);
}

void AOfficeZPlayer::FlipSprite()
{
	FVector currentScale = GetSprite()->GetComponentScale();
	currentScale.X *= -1;

	GetSprite()->SetRelativeScale3D(currentScale);
}

