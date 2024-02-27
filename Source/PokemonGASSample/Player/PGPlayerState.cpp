// Fill out your copyright notice in the Description page of Project Settings.


#include "PGPlayerState.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include <PokemonGASSample/Attribute/PGCharacterAttributeSet.h>
#include "AbilitySystemBlueprintLibrary.h"
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
	/*
	* 
	*/
	return true;
}

bool APGPlayerState::IsBattleCardSetOnTheField()
{
	/*
	* 
	*/
	return true;
}

bool APGPlayerState::IsPrizeCardSetOnTheField()
{
	/*
	* 
	*/
	return true;
}

bool APGPlayerState::SettingsForPlay()
{
	if (bGameReady)
	{
		return true;
	}

	if (!HasBattleCardInHand() && !IsBattleCardSetOnTheField())
	{
		while (!HandCards.IsEmpty())
		{
			DeckCards.Emplace(HandCards.Pop());
		}

		// 델리게이트를 통해 상대방에서 패을 확인 시켜줘야 됨.

		DeckShuffle();
		return false;
	}

	if (!IsPrizeCardSetOnTheField() && AttributeSet->GetPrizeCardCount() < AttributeSet->GetMaxPrizeCardCount())
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

}

void APGPlayerState::RemoveDeck(APGCard* InCard)
{

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

}

APGCard* APGPlayerState::GetDeckDrawCard()
{
	if (!IsEmptyDeckCards())
	{
		APGCard* Card = DeckCards.Pop();
		AddHand(Card);
		AttributeSet->SetDeckCount(AttributeSet->GetDeckCount() - 1);
		AttributeSet->SetHandCount(AttributeSet->GetHandCount() + 1);
		return Card;
	}
	return nullptr;
}

APGCard* APGPlayerState::SetPrizeCard()
{
	if (!IsEmptyDeckCards())
	{
		APGCard* Card = DeckCards.Pop();
		PrizeCards.Emplace(Card);
		AttributeSet->SetPrizeCardCount(AttributeSet->GetPrizeCardCount() + 1);
		return Card;
	}
	return nullptr;
}

bool APGPlayerState::IsEmptyDeckCards()
{
	return DeckCards.IsEmpty();
}

void APGPlayerState::SettingBenchCard()
{
	if (!GetIsSelectedDeck())
	{
		return;
	}
	
	if (!ASC)
	{
		return;
	}

	if (!AttributeSet)
	{
		return;
	}

	if (AttributeSet->GetBenchCardCount() >= AttributeSet->GetMaxBenchCardCount())
	{
		return;
	}

	AttributeSet->SetBenchCardCount(AttributeSet->GetMaxBenchCardCount() + 1);
}

void APGPlayerState::SettingBattleCard(APGCard* InCard)
{
	if (!InCard)
	{
		return;
	}

	if (OnSetBattleCard.IsBound())
	{
		OnSetBattleCard.Broadcast(InCard);
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