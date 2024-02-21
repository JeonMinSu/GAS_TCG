// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "AbilitySystemInterface.h"
#include "PGGameState.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGenericPlayerEventDelegate, int32, PlayerIndex);
UCLASS()
class POKEMONGASSAMPLE_API APGGameState : public AGameState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APGGameState();

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable)
	void ActivateFlipCoin();
	UFUNCTION(BlueprintCallable)
	void ActivateSelectDeck();
	UFUNCTION(BlueprintCallable)
	void ActivateGameStart();
	UFUNCTION()
	bool IsPlayerSelectedDeck();
	UFUNCTION()
	bool TrySetIsPlayerSelectDeck(int32 InPlayerIndex, bool bValue);

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;


public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Event)
	FOnGenericPlayerEventDelegate OnPlayerSelectDeck;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Event)
	FOnGenericPlayerEventDelegate OnPlayerGameReady;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GAS)
	TArray<bool> bPlayerSelectedDeck;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GAS)
	TArray<bool> bGameReady;
	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;
	UPROPERTY(EditAnywhere, Category = GAS)
	TArray<TSubclassOf<class UGameplayAbility>> StartAbilities;
	
};
