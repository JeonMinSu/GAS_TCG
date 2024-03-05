// Fill out your copyright notice in the Description page of Project Settings.


#include "PGPlayerController.h"
#include <Blueprint/UserWidget.h>

APGPlayerController::APGPlayerController()
{
}

void APGPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void APGPlayerController::ChangePlayerWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromParent();
		CurrentWidget = nullptr;
	}

	if (NewWidgetClass)
	{
		CurrentWidget = CreateWidget<UUserWidget>(this, NewWidgetClass);
		if (CurrentWidget)
		{
			CurrentWidget->AddToPlayerScreen();
		}
	}
}
