// Fill out your copyright notice in the Description page of Project Settings.


#include "PGCharacterAttributeSet.h"

UPGCharacterAttributeSet::UPGCharacterAttributeSet() : 
	DeckCount(0),
	MaxDeckCount(15),
	HandCount(0),
	MaxHandCount(0),
	BenchCardCount(0),
	MaxBenchCardCount(5)
{
	InitDeckCount(GetMaxDeckCount());
}

void UPGCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute & Attribute, float& NewValue)
{
	if (Attribute == GetDeckCountAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxDeckCount());
	}
}

void UPGCharacterAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	if (Attribute == GetDeckCountAttribute())
	{
		UE_LOG(LogTemp, Log, TEXT("Deck Count : %f -> %f"), OldValue, NewValue);
	}
}
