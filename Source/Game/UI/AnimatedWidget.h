// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/*----------------------------------------------------------------------------------------------------*/
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AnimatedWidget.generated.h"

/*----------------------------------------------------------------------------------------------------*/
UCLASS()
class GAME_API UAnimatedWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UAnimatedWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY(meta = (BindWidget, AllowPrivateAcces = "true"))
	class UImage* _animatedImage;

	UPROPERTY(EditAnywhere)
	class UPaperFlipbook* _defaultFlipbook;

	UPROPERTY(EditAnywhere)
	int32 _delay = 12;
	
	UPROPERTY(EditAnywhere)
	int32 _someNumberToUse = 8;

	int32 _frameCounter = 0;
};
/*----------------------------------------------------------------------------------------------------*/