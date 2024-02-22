// Fill out your copyright notice in the Description page of Project Settings.


#include "PGPlayerState.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include <PokemonGASSample/Attribute/PGCharacterAttributeSet.h>
#include <Kismet/KismetArrayLibrary.h>

APGPlayerState::APGPlayerState()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	AttributeSet = CreateDefaultSubobject<UPGCharacterAttributeSet>(TEXT("AttributeSet"));
	//ASC->SetIsReplicated(true);
}

UAbilitySystemComponent* APGPlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}

bool APGPlayerState::HasBattleCardInHand()
{
	return true;
}

bool APGPlayerState::SettingsForPlay()
{
	if (bGameReady)
	{
		return true;
	}

	if (!HasBattleCardInHand())
	{
		return false;
	}

	return true;

}

void APGPlayerState::DeckShuffle()
{
	for (int32 i = DeckCards.Num() - 1; i > 0; i--)
	{
		int32 j = FMath::FloorToInt(FMath::SRand() * (i + 1)) % DeckCards.Num();
		APGCard* Temp = DeckCards[i];
		DeckCards[i] = DeckCards[j];
		DeckCards[j] = Temp;
	}
}

//void APGPLAYE

void APGPlayerState::AddDeck(APGCard* InCard)
{
	DeckCards.Emplace(InCard);
}

void APGPlayerState::RemoveDeck(APGCard* InCard)
{

}

void APGPlayerState::AddHand(APGCard* InCard)
{

}

void APGPlayerState::RemoveHand(APGCard* InCard)
{

}

APGCard* APGPlayerState::GetDeckDrawCard()
{
	if (IsEmptyDeckCards())
	{
		APGCard* Card = DeckCards.Pop();
		AddHand(Card);
		return Card;
	}
	return nullptr;
}

bool APGPlayerState::IsEmptyDeckCards()
{
	return DeckCards.IsEmpty();
}

void APGPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();;
}

void APGPlayerState::BeginPlay()
{
	Super::BeginPlay();
}