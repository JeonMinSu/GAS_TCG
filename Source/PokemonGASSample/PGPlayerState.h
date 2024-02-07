// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "PGPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class POKEMONGASSAMPLE_API APGPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APGPlayerState();
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void BeginPlay() override;

	UFUNCTION(Blueprintcallable)
	FORCEINLINE int32 GetDeckCount() { return DeckCount; }
	UFUNCTION(Blueprintcallable)
	FORCEINLINE void SetDeckCount(const int32 InDeckCount) { DeckCount = InDeckCount; }
	UFUNCTION(Blueprintcallable)
	FORCEINLINE void IncreaseDeck() { DeckCount++; }
	UFUNCTION(Blueprintcallable)
	FORCEINLINE void DecreaseDeck() { DeckCount--; }

protected:
	virtual void PostInitializeComponents() override;

protected:
	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;

	UPROPERTY(EditAnywhere, Category = GAS)
	TArray<TSubclassOf<class UGameplayAbility>> StartAbilities;

	UPROPERTY(EditAnywhere, Category=PlayerState)
	int32 MaxDeckCount;

	UPROPERTY()
	int32 DeckCount;

	UPROPERTY()
	int32 HandCount;
};
