// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "AbilitySystemInterface.h"
#include "PGGameState.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGenericPlayerEventDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDeckSeletedDelegate);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerDeckSeletedDelegate, class APlayerState*, PlayerState);
UCLASS()
class POKEMONGASSAMPLE_API APGGameState : public AGameState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APGGameState();

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;


public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Event)
	FOnPlayerDeckSeletedDelegate OnPlayerSelectedDeckDelegate;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Event)
	FOnGenericPlayerEventDelegate OnWaitForGameReadyDelegate;

protected:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GAS)
	//TArray<bool> bPlayerSelectedDeck;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GAS)
	//TArray<bool> bGameReady;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GAS)
	TObjectPtr<class UPGFlowAbilitySystemComponent> ASC;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GAS)
	TArray<TSubclassOf<class UGameplayAbility>> StartAbilities;
	
};
