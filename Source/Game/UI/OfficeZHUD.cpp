// Fill out your copyright notice in the Description page of Project Settings.
/*----------------------------------------------------------------------------------------------------*/
#include "OfficeZHUD.h"
#include "Quest_UI.h"
/*----------------------------------------------------------------------------------------------------*/
AOfficeZHUD::AOfficeZHUD()
{
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZHUD::DrawHUD()
{
	Super::DrawHUD();
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZHUD::BeginPlay()
{
	Super::BeginPlay();

	if (_questUIClass)
	{
		_questUI = CreateWidget<UQuest_UI>(GetWorld(), _questUIClass);
		if (_questUI)
		{
			_questUI->AddToViewport();
		}
	}
}
/*----------------------------------------------------------------------------------------------------*/
void AOfficeZHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
}
/*----------------------------------------------------------------------------------------------------*/