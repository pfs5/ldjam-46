// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "OfficeZNPC.h"
#include "PaperFlipbookComponent.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/CollisionProfile.h"
#include "PaperSpriteComponent.h"
/*----------------------------------------------------------------------------------------------------*/
AOfficeZNPC::AOfficeZNPC()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	
	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("FlipbookComponent"));
	FlipbookComponent->SetupAttachment(RootComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
	BoxComponent->SetBoxExtent(FVector(8.f, 32.f, 16.f));
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->SetRelativeLocation(FVector(0.f, 0.f, 2.f));

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent"));
	SpriteComponent->SetupAttachment(RootComponent);
	SpriteComponent->SetRelativeLocation(FVector(0.f, -2.f, -15.f));
}
/*----------------------------------------------------------------------------------------------------*/