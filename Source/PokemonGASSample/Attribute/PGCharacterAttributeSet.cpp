// Fill out your copyright notice in the Description page of Project Settings.


#include "PGCharacterAttributeSet.h"

UPGCharacterAttributeSet::UPGCharacterAttributeSet() : 
	DeckCount(0),
	MaxDeckCount(30),
	HandCount(0),
	MaxHandCount(7),
	BenchCardCount(0),
	MaxBenchCardCount(5),
	BattleCardCount(0),
	MaxBattleCardCount(1),
	PrizeCardCount(0),
	MaxPrizeCardCount(3),
	DiscardPileCardCount(0),
	MaxDiscardPileCardCount(30)
{

}

void UPGCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute & Attribute, float& NewValue)
{
	if (Attribute == GetDeckCountAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxDeckCount());
	}

	if (Attribute == GetBenchCardCountAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxBenchCardCount());
	}

	if (Attribute == GetPrizeCardCountAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxPrizeCardCount());
	}

	if (Attribute == GetBattleCardCountAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxBattleCardCount());
	}

	if (Attribute == GetDiscardPileCardCountAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxDiscardPileCardCount());
	}

}

void UPGCharacterAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	if (Attribute == GetDeckCountAttribute())
	{
		UE_LOG(LogTemp, Log, TEXT("Deck Count : %f -> %f"), OldValue, NewValue);
	}

	if (Attribute == GetHandCountAttribute())
	{
		UE_LOG(LogTemp, Log, TEXT("Hand Count : %f -> %f"), OldValue, NewValue);
	}

	if (Attribute == GetBenchCardCountAttribute())
	{
		UE_LOG(LogTemp, Log, TEXT("Bench Count : %f -> %f"), OldValue, NewValue);
	}

	if (Attribute == GetPrizeCardCountAttribute())
	{
		UE_LOG(LogTemp, Log, TEXT("Prize Count : %f -> %f"), OldValue, NewValue);
	}

	if (Attribute == GetDiscardPileCardCountAttribute())
	{
		UE_LOG(LogTemp, Log, TEXT("Discard Pile Count : %f -> %f"), OldValue, NewValue);
	}

}
