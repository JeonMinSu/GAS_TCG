// Fill out your copyright notice in the Description page of Project Settings.


#include "PGPlayerState.h"
#include "AbilitySystemComponent.h"
#include "Component/PGPlayerASC.h"
#include "Attribute/PGCharacterAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Card/PGCard.h"
#include "Card/PGDeckData.h"
#include "Tag/PGGameplayTag.h"
#include <Kismet/KismetArrayLibrary.h>
#include "Engine/DataTable.h"
#include "Card/PGMonster.h"

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
	for (const APGCard* HandCard : GetCardsInHand())
	{
		if (HandCard->GetAbilitySystemComponent()->HasMatchingGameplayTag(PGTAG_CARD_TYPE_MONSTER))
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

APGCard* APGPlayerState::GetBattleCard()
{
	return BattleCard;
}

APGMonster* APGPlayerState::GetBattleMonster()
{
	TArray<AActor*> Actors;
	BattleCard->GetAllChildActors(Actors);
	for (AActor* Actor : Actors)
	{
		APGMonster* Monster = Cast<APGMonster>(Actor);
		if (Monster)
		{
			return Monster;
		}
	}

	return nullptr;
}

void APGPlayerState::SetBattleCard(APGCard* Card)
{
	if (Card == nullptr)
	{
		BattleCard = nullptr;
	}
	else if (Card->GetAbilitySystemComponent()->HasMatchingGameplayTag(PGTAG_CARD_TYPE_MONSTER))
	{
		BattleCard = Card;
	}
}

void APGPlayerState::ReturnCardsInHandToDeck()
{
	for(APGCard* HandCard : GetCardsInHand())
	{
		UAbilitySystemComponent* CardASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HandCard);
		if (CardASC)
		{
			FGameplayTagContainer TagContainer(PGTAG_CARD_ACTION_2DECK);
			CardASC->TryActivateAbilitiesByTag(TagContainer);
		}
	}
}

void APGPlayerState::SetGameOver()
{
	bGameOvered = true;
}

bool APGPlayerState::IsPrizeCardSetOnTheField()
{
	return GetCardsInPrize().Num() != 0;
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
	for (int32 i = InstancedCards.Num() - 1; i > 0; i--)
	{
		int32 j = FMath::FloorToInt(FMath::SRand() * (i + 1)) % InstancedCards.Num();
		APGCard* Temp = InstancedCards[i];
		InstancedCards[i] = InstancedCards[j];
		InstancedCards[j] = Temp;
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
	}
}

APGCard* APGPlayerState::GetDeckDrawCard()
{
	if (!IsEmptyDeckCards())
	{
		APGCard* Card = const_cast<APGCard*>(GetCardsInDeck()[0]);
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
	}
}

bool APGPlayerState::IsEmptyDeckCards()
{
	return GetCardsInDeck().IsEmpty();
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

bool APGPlayerState::IsHandFull()
{
	return AttributeSet->GetHandCount() >= AttributeSet->GetMaxHandCount();
}

TArray<APGCard*> APGPlayerState::GetCardsWithTag(FGameplayTag GameplayTag)
{
	TArray<APGCard*> ReturnValue;

	for (APGCard* Card : InstancedCards)
	{
		if (Card->GetAbilitySystemComponent()->HasMatchingGameplayTag(GameplayTag))
		{
			ReturnValue.Add(Card);
		}
	}

	return ReturnValue;
}

TArray<APGCard*> APGPlayerState::GetCardsInDeck()
{
	return GetCardsWithTag(PGTAG_CARD_STATUS_DECK);
}

TArray<APGCard*> APGPlayerState::GetCardsInHand()
{
	return GetCardsWithTag(PGTAG_CARD_STATUS_HAND);
}

TArray<APGCard*> APGPlayerState::GetCardsInPrize()
{
	return GetCardsWithTag(PGTAG_CARD_STATUS_PRIZE);
}

TArray<APGCard*> APGPlayerState::GetCardsInTrash()
{
	return GetCardsWithTag(PGTAG_CARD_STATUS_TRASH);
}
