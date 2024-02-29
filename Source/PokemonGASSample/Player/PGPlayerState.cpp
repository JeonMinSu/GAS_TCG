// Fill out your copyright notice in the Description page of Project Settings.


#include "PGPlayerState.h"
#include "AbilitySystemComponent.h"
#include "Component/PGFlowAbilitySystemComponent.h"
#include "Attribute/PGCharacterAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Card/PGCard.h"
#include <Kismet/KismetArrayLibrary.h>

APGPlayerState::APGPlayerState()
{
	ASC = CreateDefaultSubobject<UPGFlowAbilitySystemComponent>(TEXT("FlowASC"));
	AttributeSet = CreateDefaultSubobject<UPGCharacterAttributeSet>(TEXT("AttributeSet"));
	BattleCard = nullptr;
	bSelectedDeck = false;
	//ASC->SetIsReplicated(true);
}

UAbilitySystemComponent* APGPlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}

bool APGPlayerState::HasBattleCardInHand()
{
	for (const auto HandCard : HandCards)
	{
		if (HandCard->GetCardType() == ECardType::E_Battle)
		{
			return true;
		}
	}
	return false;
}

bool APGPlayerState::IsBattleCardSetOnTheField()
{
	return BattleCard != nullptr;
}

bool APGPlayerState::IsPrizeCardSetOnTheField()
{
	return PrizeCards.Num() != 0;
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

		// 델리게이트를 통해 상대방에서 패를 확인 시켜줘야 됨.

		DeckShuffle();
		return false;
	}

	if (!IsPrizeCardSetOnTheField())
	{
		return false;
	}

	return true;
}

void APGPlayerState::SpawnForSelectedDeck()
{
	if (bSelectedDeck)
	{
		return;
	}

	UWorld* const World = GetWorld();

	FDeckCardInfo DeckCardData = DeckCardDatas[DeckIndex];
	for (TSubclassOf<APGCard> Card : DeckCardData.DeckCards)
	{
		AddDeck(World->SpawnActor<APGCard>(*Card));
	}
	bSelectedDeck = true;
	DeckShuffle();
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
	if (InCard)
	{
		DeckCards.Emplace(InCard);
	}
}

void APGPlayerState::RemoveDeck(APGCard* InCard)
{
	if (InCard && DeckCards.Contains(InCard))
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

}

APGCard* APGPlayerState::GetDeckDrawCard()
{
	if (!IsEmptyDeckCards())
	{
		APGCard* Card = DeckCards.Pop();
		AddHand(Card);
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
	if (!IsSelectedDeck())
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

	//if (AttributeSet->GetBenchCardCount() >= AttributeSet->GetMaxBenchCardCount())
	//{
	//	return;
	//}
}
