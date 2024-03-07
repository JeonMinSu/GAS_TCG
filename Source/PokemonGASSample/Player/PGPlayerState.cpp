// Fill out your copyright notice in the Description page of Project Settings.


#include "PGPlayerState.h"
#include "AbilitySystemComponent.h"
#include "Component/PGPlayerASC.h"
#include "Attribute/PGCharacterAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Card/PGCard.h"
#include "Card/PGDeckData.h"
#include <Kismet/KismetArrayLibrary.h>

APGPlayerState::APGPlayerState()
{
	ASC = CreateDefaultSubobject<UPGPlayerASC>(TEXT("PlayerASC"));
	AttributeSet = CreateDefaultSubobject<UPGCharacterAttributeSet>(TEXT("AttributeSet"));
	BattleCard = nullptr;
	bSelectedDeck = false;
	SpawningDeckData = nullptr;
	//ASC->SetIsReplicated(true);
}

UAbilitySystemComponent* APGPlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}

bool APGPlayerState::HasBattleCardInHand()
{
	for (const auto HandCard : InHandCards)
	{
		//if (HandCard->GetCardType() == ECardType::E_Battle)
		//{
		//	return true;
		//}
	}
	return true;
}

bool APGPlayerState::IsBattleCardSetOnTheField()
{
	return BattleCard != nullptr;
}

AActor* APGPlayerState::GetBattleCard()
{
	return BattleCard;
}

void APGPlayerState::ReturnCardsInHandToDeck()
{
	if (!HasBattleCardInHand() && !IsBattleCardSetOnTheField())
	{
		while (!InHandCards.IsEmpty())
		{
			APGCard* HandCard = InHandCards.Pop();
			InDeckCards.Add(HandCard);
		}
	}

	// need to change card's ability tags how?
}

bool APGPlayerState::IsPrizeCardSetOnTheField()
{
	return InPrizeCards.Num() != 0;
}	

bool APGPlayerState::SettingsForPlay()
{
	if (bGameReady)
	{
		return true;
	}

	if (!HasBattleCardInHand() && !IsBattleCardSetOnTheField())
	{
		while (!InHandCards.IsEmpty())
		{
			InDeckCards.Emplace(InHandCards.Pop());
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

TArray<class UPGDeckData*> APGPlayerState::GetSelectableDeckData()
{
	return SelectableDeckData;
}

void APGPlayerState::SpawnForSelectedDeck()
{
	if (bSelectedDeck || SpawningDeckData == nullptr)
	{
		return;
	}

	UWorld* const World = GetWorld();

	for (const auto& CardData : SpawningDeckData->DeckMap)
	{
		for (int i = 0; i < CardData.Value; i++)
		{
			AActor* SpawnedActor = World->SpawnActor(CardData.Key);
			if (SpawnedActor)
			{
				APGCard* Card = Cast<APGCard>(SpawnedActor);
				if (Card)
				{
					Card->SetCardOwner(this);
					InstancedCards.Add(Card);
				}
			}
		}
	}

	for (APGCard* Card : InstancedCards)
	{
		AddDeck(Card);
	}

	bSelectedDeck = true;
}

void APGPlayerState::SetSpawningDeck(UPGDeckData* DeckData)
{
	SpawningDeckData = DeckData;
}

void APGPlayerState::DeckShuffle()
{
	for (int32 i = InDeckCards.Num() - 1; i > 0; i--)
	{
		int32 j = FMath::FloorToInt(FMath::SRand() * (i + 1)) % InDeckCards.Num();
		APGCard* Temp = InDeckCards[i];
		InDeckCards[i] = InDeckCards[j];
		InDeckCards[j] = Temp;
	}
}

void APGPlayerState::AddDeck(APGCard* InCard)
{
	if (InCard != nullptr)
	{
		UAbilitySystemComponent* CardASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InCard);
		if (CardASC)
		{
			FGameplayTagContainer TagContainer(PGTAG_CARD_ACTION_2DECK);
			CardASC->TryActivateAbilitiesByTag(TagContainer);
		}
		InDeckCards.Add(InCard);
	}
}

void APGPlayerState::RemoveDeck(APGCard* InCard)
{
	if (InCard && InDeckCards.Contains(InCard))
	{
		InDeckCards.Remove(InCard);
	}
}

void APGPlayerState::AddHand(APGCard* InCard)
{
	if (InCard)
	{
		UAbilitySystemComponent* CardASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InCard);
		if (CardASC)
		{
			FGameplayTagContainer TagContainer(PGTAG_CARD_ACTION_2HAND);
			CardASC->TryActivateAbilitiesByTag(TagContainer);
		}
		InHandCards.Add(InCard);
	}
}

void APGPlayerState::RemoveHand(APGCard* InCard)
{

}

APGCard* APGPlayerState::GetDeckDrawCard()
{
	if (!IsEmptyDeckCards())
	{
		APGCard* Card = InDeckCards.Pop();
		return Card;
	}
	return nullptr;
}

void APGPlayerState::SetPrizeCard(int32 InAmount)
{
	for (int i = 0; i < InAmount; i++)
	{
		if (IsEmptyDeckCards())
		{
			return;
		}
		InPrizeCards.Emplace(InDeckCards.Pop());
	}
	//if (!IsEmptyDeckCards())
	//{
	//	APGCard* Card = DeckCards.Pop();
	//	PrizeCards.Emplace(Card);
	//}
}

bool APGPlayerState::IsEmptyDeckCards()
{
	return InDeckCards.IsEmpty();
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
}

void APGPlayerState::DrawCard(int32 InAmount)
{
	for (int i = 0; i < InAmount; i++)
	{
		if (IsEmptyDeckCards())
		{
			return;
		}
		AddHand(GetDeckDrawCard());
	}
}
