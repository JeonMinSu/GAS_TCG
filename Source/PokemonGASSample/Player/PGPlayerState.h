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

USTRUCT(BlueprintType)
struct POKEMONGASSAMPLE_API FDeckCardInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "CAS Card")
	TArray<TSubclassOf<class APGCard>> DeckCards;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSetGameplayTag, FGameplayTag, GameplayTag);
UCLASS()
class POKEMONGASSAMPLE_API APGPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APGPlayerState();
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	//UFUNCTION(BlueprintCallable, Category = Player)
	//FORCEINLINE void SetIsGameReady(const bool bInGameReady) { bGameReady = bInGameReady; }
	//UFUNCTION(BlueprintCallable, Category = Player)
	//FORCEINLINE void SetIsSelectedDeck(const bool bInSelectedDeck) { bSelectedDeck = bInSelectedDeck; }

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
	class APGCard* GetDeckDrawCard();
	UFUNCTION(BlueprintCallable, Category = Player)
	class APGCard* SetPrizeCard();
	UFUNCTION(BlueprintCallable, Category = Player)
	bool IsEmptyDeckCards();
	UFUNCTION(BlueprintCallable, Category = Player)
	void SettingBenchCard();

	UFUNCTION(BlueprintCallable, Category = Player)
	FORCEINLINE int32 GetDeckCount() { return DeckCards.Num(); }
	UFUNCTION(BlueprintCallable, Category = Player)
	FORCEINLINE int32 GetHandCount() { return HandCards.Num(); }
	UFUNCTION(BlueprintCallable, Category = Player)
	FORCEINLINE int32 GetPrizeCount() { return PrizeCards.Num(); }
	UFUNCTION(BlueprintCallable, Category = Player)
	FORCEINLINE int32 GetDiscardPileCardCount() { return DiscardPileCards.Num(); };
	//UFUNCTION(BlueprintCallable, Category = "Player | Card")
	//void SettingBattleCard(class APGCard* InCard);

protected:
	bool IsPrizeCardSetOnTheField();

public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	//bool bIsFirstTurn;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Event)
	FOnSetGameplayTag OnSetGameplayTag;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	bool bGameReady;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	bool bSelectedDeck;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GAS)
	int32 DeckIndex;

	UPROPERTY(EditAnywhere, Category = GAS)
	TArray<FDeckCardInfo> DeckCardDatas;

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
	TObjectPtr<class UPGFlowAbilitySystemComponent> ASC;
	UPROPERTY()
	TObjectPtr<class UPGCharacterAttributeSet> AttributeSet;

};
