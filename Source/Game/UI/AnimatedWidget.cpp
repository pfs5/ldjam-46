// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimatedWidget.h"
#include "Components/Image.h"
#include "PaperFlipbook.h"
#include "PaperSprite.h"

//--------------------------------------------------------------------------------------------------
UAnimatedWidget::UAnimatedWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}
//--------------------------------------------------------------------------------------------------
/*override*/
void UAnimatedWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (_defaultFlipbook == nullptr)
	{
		return;
	}

	_counter += InDeltaTime;
	const float animationInterval = 1.f / _defaultFlipbook->GetFramesPerSecond();

	if (_counter >= animationInterval)
	{
		_counter = 0.f;
		_frameCounter = (_frameCounter + 1) % _defaultFlipbook->GetNumKeyFrames();

		UPaperSprite* sprite = _defaultFlipbook->GetSpriteAtFrame(_frameCounter);
		if (sprite == nullptr)
		{
			return;
		}

		if (_animatedImage != nullptr)
		{
			_animatedImage->SetBrushFromAtlasInterface(sprite, false);
		}
	}
}
/*----------------------------------------------------------------------------------------------------*/
bool UAnimatedWidget::Initialize()
{
	bool ret = Super::Initialize();

	if (_defaultFlipbook == nullptr)
	{
		return false;
	}

	UPaperSprite* sprite = _defaultFlipbook->GetSpriteAtFrame(_frameCounter);
	if (sprite == nullptr)
	{
		return false;
	}

	if (_animatedImage == nullptr)
	{
		return false;
	}

	_animatedImage->SetBrushFromAtlasInterface(sprite, false);

	return ret;
}
/*----------------------------------------------------------------------------------------------------*/