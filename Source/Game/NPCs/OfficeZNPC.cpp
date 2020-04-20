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
	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("FlipbookComponent"));
	FlipbookComponent->AttachToComponent(_sprite, FAttachmentTransformRules::KeepRelativeTransform);

	_overlappBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlappBoxComponent"));
	_overlappBoxComponent->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
	_overlappBoxComponent->SetBoxExtent(FVector(8.f, 32.f, 16.f));
	_overlappBoxComponent->AttachToComponent(_sprite, FAttachmentTransformRules::KeepRelativeTransform);
	_overlappBoxComponent->SetRelativeLocation(FVector(0.f, 0.f, 2.f));
}
/*----------------------------------------------------------------------------------------------------*/