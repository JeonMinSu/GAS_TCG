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

	//UFUNCTION(Blueprintcallable)
	//FORCEINLINE void SetPlayerDeckIndex(const int32 InDeckIndex) { DeckIndex = InDeckIndex; }
	//UFUNCTION(Blueprintcallable)
	//FORCEINLINE int32 GetPlayerDeckIndex() const { return DeckIndex; }

	//UFUNCTION(Blueprintcallable)
	//FORCEINLINE int32 GetDeckCount() const { return DeckCount; }
	//UFUNCTION(Blueprintcallable)
	//FORCEINLINE int32 GetHandCount() const { return HandCount; }
	//
	//UFUNCTION(Blueprintcallable)
	//FORCEINLINE void SetDeckCount(const int32 InDeckCount) { DeckCount = InDeckCount; }
	//UFUNCTION(Blueprintcallable)
	//FORCEINLINE void SetHandCount(const int32 InHandCount) { HandCount = InHandCount; }

	//UFUNCTION(Blueprintcallable)
	//FORCEINLINE void IncreaseHand() { HandCount++; }
	//UFUNCTION(Blueprintcallable)
	//FORCEINLINE void DecreaseHand() { HandCount--; }

	//UFUNCTION(Blueprintcallable)
	//FORCEINLINE void IncreaseDeck() { DeckCount++; }
	//UFUNCTION(Blueprintcallable)
	//FORCEINLINE void DecreaseDeck() { DeckCount--; }

protected:
	virtual void PostInitializeComponents() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	bool bIsFirstTurn;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Event)
	FOnSetGameplayTag OnSetGameplayTag;

protected:
	UPROPERTY(EditAnywhere, Category = GAS)
	int32 DeckIndex;

	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;
	UPROPERTY()
	TObjectPtr<class UPGCharacterAttributeSet> AttributeSet;

};
