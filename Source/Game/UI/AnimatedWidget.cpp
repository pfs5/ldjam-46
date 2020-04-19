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

	++_frameCounter;

	if (_frameCounter > _delay * _someNumberToUse)
	{
		_frameCounter = 0;
	}

	if (_delay == 0)
	{
		return;
	}

	UPaperSprite* sprite = _defaultFlipbook->GetSpriteAtFrame(_frameCounter / _delay);
	if (sprite == nullptr)
	{
		return;
	}
	
	if (_animatedImage != nullptr)
	{
		_animatedImage->SetBrushFromAtlasInterface(sprite, false);
	}
}
/*----------------------------------------------------------------------------------------------------*/