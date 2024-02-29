// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "PGCharacterAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class POKEMONGASSAMPLE_API UPGCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UPGCharacterAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	ATTRIBUTE_ACCESSORS(UPGCharacterAttributeSet, DeckCount);
	ATTRIBUTE_ACCESSORS(UPGCharacterAttributeSet, MaxDeckCount);
	
	ATTRIBUTE_ACCESSORS(UPGCharacterAttributeSet, HandCount);
	ATTRIBUTE_ACCESSORS(UPGCharacterAttributeSet, MaxHandCount);
	
	ATTRIBUTE_ACCESSORS(UPGCharacterAttributeSet, BenchCardCount);
	ATTRIBUTE_ACCESSORS(UPGCharacterAttributeSet, MaxBenchCardCount);
	
	ATTRIBUTE_ACCESSORS(UPGCharacterAttributeSet, BattleCardCount);
	ATTRIBUTE_ACCESSORS(UPGCharacterAttributeSet, MaxBattleCardCount)

	ATTRIBUTE_ACCESSORS(UPGCharacterAttributeSet, PrizeCardCount);
	ATTRIBUTE_ACCESSORS(UPGCharacterAttributeSet, MaxPrizeCardCount);
	
	ATTRIBUTE_ACCESSORS(UPGCharacterAttributeSet, DiscardPileCardCount);
	ATTRIBUTE_ACCESSORS(UPGCharacterAttributeSet, MaxDiscardPileCardCount);

protected:
	UPROPERTY(BlueprintReadOnly, Category = Deck, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData DeckCount;
	UPROPERTY(BlueprintReadOnly, Category = Deck, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxDeckCount;

	UPROPERTY(BlueprintReadOnly, Category = Hand, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData HandCount;
	UPROPERTY(BlueprintReadOnly, Category = Hand, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHandCount;

	UPROPERTY(BlueprintReadOnly, Category = Bench, Meta = (AllowPrivateAceess = true))
	FGameplayAttributeData BenchCardCount;
	UPROPERTY(BlueprintReadOnly, Category = Bench, Meta = (AllowPrivateAceess = true))
	FGameplayAttributeData MaxBenchCardCount;

	UPROPERTY(BlueprintReadOnly, Category = Battle, Meta = (AllowPrivateAceess = true))
	FGameplayAttributeData BattleCardCount;
	UPROPERTY(BlueprintReadOnly, Category = Battle, Meta = (AllowPrivateAceess = true))
	FGameplayAttributeData MaxBattleCardCount;

	UPROPERTY(BlueprintReadOnly, Category = Prize, Meta = (AllowPrivateAceess = true))
	FGameplayAttributeData PrizeCardCount;
	UPROPERTY(BlueprintReadOnly, Category = Prize, Meta = (AllowPrivateAceess = true))
	FGameplayAttributeData MaxPrizeCardCount;

	UPROPERTY(BlueprintReadOnly, Category = Prize, Meta = (AllowPrivateAceess = true))
	FGameplayAttributeData DiscardPileCardCount;
	UPROPERTY(BlueprintReadOnly, Category = Prize, Meta = (AllowPrivateAceess = true))
	FGameplayAttributeData MaxDiscardPileCardCount;
};
