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

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSettingForPlay);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSetGameplayTag, FGameplayTag, GameplayTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSetBattleCard, class APGCard*, InCard);

UCLASS()
class POKEMONGASSAMPLE_API APGPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APGPlayerState();
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void BeginPlay() override;

	//UFUNCTION(BlueprintCallable, Category = Player)
	//FORCEINLINE void SetIsGameReady(const bool bInGameReady) { bGameReady = bInGameReady; }
	UFUNCTION(BlueprintCallable, Category = Player)
	FORCEINLINE void SetIsSelectedDeck(const bool bInSelectedDeck) { bSelectedDeck = bInSelectedDeck; }

	UFUNCTION(BlueprintCallable, Category = Player)
	FORCEINLINE bool GetIsGameReady() const { return bGameReady; }
	UFUNCTION(BlueprintCallable, Category = Player)
	FORCEINLINE bool GetIsSelectedDeck() const { return bSelectedDeck; }

	UFUNCTION(BlueprintCallable, Category = Player)
	bool HasBattleCardInHand();
	UFUNCTION(BlueprintCallable, Category = Player)
	bool IsBattleCardSetOnTheField();
	UFUNCTION(BlueprintCallable, Category = Player)
	bool SettingsForPlay();

	UFUNCTION(BlueprintCallable, Category = "Player | Card")
	void DeckShuffle();
	UFUNCTION(BlueprintCallable, Category = "Player | Card")
	void AddDeck(class APGCard* InCard);
	UFUNCTION(BlueprintCallable, Category = "Player | Card")
	void RemoveDeck(class APGCard* InCard);
	UFUNCTION(BlueprintCallable, Category = "Player | Card")
	void AddHand(class APGCard* InCard);
	UFUNCTION(BlueprintCallable, Category = "Player | Card")
	void RemoveHand(class APGCard* InCard);
	UFUNCTION(BlueprintCallable, Category = "Player | Card")
	class APGCard* GetDeckDrawCard();
	UFUNCTION(BlueprintCallable, Category = "Player | Card")
	class APGCard* SetPrizeCard();
	UFUNCTION(BlueprintCallable, Category = "Player | Card")
	bool IsEmptyDeckCards();
	UFUNCTION(BlueprintCallable, Category = "Player | Card")
	void SettingBenchCard();
	UFUNCTION(BlueprintCallable, Category = "Player | Card")
	void SettingBattleCard(class APGCard* InCard);

protected:
	virtual void PostInitializeComponents() override;
	bool IsPrizeCardSetOnTheField();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	bool bIsFirstTurn;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Event)
	FOnSetGameplayTag OnSetGameplayTag;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Event)
	FOnSettingForPlay OnSettingForPlay;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Event)
	FOnSetBattleCard OnSetBattleCard;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	bool bGameReady;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	bool bSelectedDeck;

	UPROPERTY(EditAnywhere, Category = GAS)
	int32 DeckIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player | Card")
	TArray<TObjectPtr<class APGCard>> DeckCards;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player | Card")
	TArray<TObjectPtr<class APGCard>> HandCards;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player | Card")
	TArray<TObjectPtr<class APGCard>> PrizeCards;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player | Card")
	TArray<TObjectPtr<class APGCard>> DiscardPileCards;

	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UPGFlowAbilitySystemComponent> ASC;
	UPROPERTY()
	TObjectPtr<class UPGCharacterAttributeSet> AttributeSet;

};
