// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "OfficeZNPC.h"
#include "PaperFlipbookComponent.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/CollisionProfile.h"
#include "PaperSpriteComponent.h"
#include "../QuestSystem/QuestManager.h"
#include "../UI/OfficeZHUD.h"
#include "Kismet/GameplayStatics.h"
#include "../UI/HudWidget_UI.h"
/*----------------------------------------------------------------------------------------------------*/
AOfficeZNPC::AOfficeZNPC()
{
	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	
	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("FlipbookComponent"));
	FlipbookComponent->AttachToComponent(_sprite, FAttachmentTransformRules::KeepRelativeTransform);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
	BoxComponent->SetBoxExtent(FVector(8.f, 32.f, 16.f));
	BoxComponent->AttachToComponent(_sprite, FAttachmentTransformRules::KeepRelativeTransform);
	BoxComponent->SetRelativeLocation(FVector(0.f, 0.f, 2.f));

	/*SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent"));
	SpriteComponent->SetupAttachment(RootComponent);
	SpriteComponent->SetRelativeLocation(FVector(0.f, -2.f, -15.f));*/
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZNPC::StopInteractingWith()
{
	Super::StopInteractingWith();

	AQuestManager* questManager = GetQuestManager(this);
	if (questManager == nullptr)
	{
		return;
	}
	
	//if (questManager->IsActorPartOfActiveQuest(this))
	if(true)
	{
		AOfficeZHUD* hud = Cast<AOfficeZHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
		if (hud != nullptr)
		{
			UHudWidget_UI* hudWidget = hud->GetHudWidget();
			if (hudWidget != nullptr)
			{
				hudWidget->HideBossQuestDialogue();
			}
		}
	}
}
/*----------------------------------------------------------------------------------------------------*/
float AOfficeZNPC::GetInteractDuration() const
{
	AQuestManager* questManager = GetQuestManager(this);
	if (questManager == nullptr)
	{
		return Super::GetInteractDuration();
	}

	if (!questManager->IsActorPartOfActiveQuest(this))
	{
		return Super::GetInteractDuration();
	}
	else
	{
		return 9999999.f;
	}
}
/*----------------------------------------------------------------------------------------------------*/