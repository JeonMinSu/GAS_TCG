// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "Tag/PGGameplayTag.h"
#include "PGPlayerState.generated.h"

/**
 * 
 */

//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGenericPlayerEventDelegate);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSetBattleCard, class APGCard*, InCard);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSetGameplayTag, FGameplayTag, GameplayTag);
UCLASS()
class POKEMONGASSAMPLE_API APGPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APGPlayerState();
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable, Category = Player)
	FORCEINLINE bool IsGameReady() const { return bGameReady; }
	UFUNCTION(BlueprintCallable, Category = Player)
	FORCEINLINE bool IsSelectedDeck() const { return bSelectedDeck; }

	UFUNCTION(BlueprintCallable, Category = Player)
	bool HasBattleCardInHand();
	UFUNCTION(BlueprintCallable, Category = Player)
	bool IsBattleCardSetOnTheField();
	UFUNCTION(BlueprintCallable, Category = Player)
	bool SettingsForPlay();

	UFUNCTION(BlueprintCallable, Category = Player)
	void SpawnForSelectedDeck();

	UFUNCTION(BlueprintCallable, Category = Player)
	void DeckShuffle();
	UFUNCTION(BlueprintCallable, Category = Player)
	void AddDeck(class APGCard* InCard);
	UFUNCTION(BlueprintCallable, Category = Player)
	void RemoveDeck(class APGCard* InCard);
	UFUNCTION(BlueprintCallable, Category = Player)
	void AddHand(class APGCard* InCard);
	UFUNCTION(BlueprintCallable, Category = Player)
	void RemoveHand(class APGCard* InCard);
	UFUNCTION(BlueprintCallable, Category = Player)
	void SetPrizeCard(int32 InAmount);
	UFUNCTION(BlueprintCallable, Category = Player)
	bool IsEmptyDeckCards();
	UFUNCTION(BlueprintCallable, Category = Player)
	void SettingBenchCard();
	UFUNCTION(BlueprintCallable, Category = Player)
	void DrawCard(int32 InAmount);

	UFUNCTION(BlueprintCallable, Category = Player)
	FORCEINLINE int32 GetDeckCount() { return DeckCards.Num(); }
	UFUNCTION(BlueprintCallable, Category = Player)
	FORCEINLINE int32 GetHandCount() { return HandCards.Num(); }
	UFUNCTION(BlueprintCallable, Category = Player)
	FORCEINLINE int32 GetPrizeCount() { return PrizeCards.Num(); }
	UFUNCTION(BlueprintCallable, Category = Player)
	FORCEINLINE int32 GetDiscardPileCardCount() { return DiscardPileCards.Num(); };

	UFUNCTION(BlueprintCallable, Category = Player)
	void ReturnCardsInHandToDeck();

protected:
	bool IsPrizeCardSetOnTheField();

	UFUNCTION(BlueprintCallable, Category = Player)
	class APGCard* GetDeckDrawCard();

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Event)
	FOnSetGameplayTag OnSetGameplayTag;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	bool bGameReady;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	bool bSelectedDeck;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Card)
	TObjectPtr<class UPGDeckData> DeckData;

	UPROPERTY(EditAnywhere, Category = Card)
	TArray<TObjectPtr<class APGCard>> InstancedCards;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class APGCard> BattleCard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player | Card")
	TArray<TObjectPtr<class APGCard>> DeckCards;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player | Card")
	TArray<TObjectPtr<class APGCard>> HandCards;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player | Card")
	TArray<TObjectPtr<class APGCard>> PrizeCards;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player | Card")
	TArray<TObjectPtr<class APGCard>> DiscardPileCards;

	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UPGPlayerASC> ASC;
	UPROPERTY()
	TObjectPtr<class UPGCharacterAttributeSet> AttributeSet;

};
