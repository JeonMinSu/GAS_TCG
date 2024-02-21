// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include <PokemonGASSample/Tag/PGGameplayTag.h>
#include "PGPlayerState.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSetGameplayTag, FGameplayTag, GameplayTag);

UCLASS()
class POKEMONGASSAMPLE_API APGPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APGPlayerState();
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = Player)
	FORCEINLINE void SetIsGameReady(const bool bInGameReady) { bGameReady = bInGameReady; }
	UFUNCTION(BlueprintCallable, Category = Player)
	FORCEINLINE void SetIsSelectedDeck(const bool bInSelectedDeck) { bSelectedDeck = bInSelectedDeck; }

	UFUNCTION(BlueprintCallable, Category = Player)
	FORCEINLINE bool GetIsGameReady() const { return bGameReady; }
	UFUNCTION(BlueprintCallable, Category = Player)
	FORCEINLINE bool GetIsSelectedDeck() const { return bSelectedDeck; }

protected:
	virtual void PostInitializeComponents() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	bool bIsFirstTurn;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Event)
	FOnSetGameplayTag OnSetGameplayTag;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	bool bGameReady;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	bool bSelectedDeck;

	UPROPERTY(EditAnywhere, Category = GAS)
	int32 DeckIndex;

	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;
	UPROPERTY()
	TObjectPtr<class UPGCharacterAttributeSet> AttributeSet;

};
