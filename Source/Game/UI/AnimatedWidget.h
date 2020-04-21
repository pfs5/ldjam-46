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
	virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget, AllowPrivateAcces = "true"))
	class UImage* _animatedImage;

	UPROPERTY(EditAnywhere)
	class UPaperFlipbook* _defaultFlipbook;

	int32 _frameCounter = 0;
	
	float _counter = 0.f;
};
/*----------------------------------------------------------------------------------------------------*/