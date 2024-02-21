// Fill out your copyright notice in the Description page of Project Settings.


#include "PGPlayerState.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include <PokemonGASSample/Attribute/PGCharacterAttributeSet.h>

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

void APGPlayerState::AddDeck(APGCard* InCard)
{
	if (InCard)
	{
		DeckCards.Emplace(InCard);
	}
}

void APGPlayerState::RemoveDeck(APGCard* InCard)
{
	if (InCard)
	{
		DeckCards.Remove(InCard);
	}
}

void APGPlayerState::AddHand(APGCard* InCard)
{
	if (InCard)
	{
		HandCards.Emplace(InCard);
	}
}

void APGPlayerState::RemoveHand(APGCard* InCard)
{
	if (InCard)
	{
		HandCards.Remove(InCard);
	}
}

void APGPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();;
}

void APGPlayerState::BeginPlay()
{
	Super::BeginPlay();
}