// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PGPlayerController.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameReady);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPrepareGame);

UCLASS()
class POKEMONGASSAMPLE_API APGPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	APGPlayerController();

	UFUNCTION(BlueprintCallable, Category = UMG)
	void ChangePlayerWidget(TSubclassOf<UUserWidget> NewWidgetClass);
	UFUNCTION(BlueprintCallable, Category = UMG)
	UUserWidget* GetCurrentWidget() const { return CurrentWidget; }

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Event)
	FOnPrepareGame OnPrepareGame;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Event)
	FOnGameReady OnGameReady;

protected:
	UPROPERTY(EditAnywhere, Category = UMG)
	TObjectPtr<UUserWidget> CurrentWidget;

};
