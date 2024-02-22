// Fill out your copyright notice in the Description page of Project Settings.


#include "PGGameState.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include <PokemonGASSample/Tag/PGGameplayTag.h>
#include <PokemonGASSample/GA/PGGA_DeckSelect.h>
#include <PokemonGASSample/Player/PGPlayerState.h>

APGGameState::APGGameState()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	ASC->SetIsReplicated(true);
}

void APGGameState::BeginPlay()
{
	Super::BeginPlay();
}

UAbilitySystemComponent* APGGameState::GetAbilitySystemComponent() const
{
	return ASC;
}

void APGGameState::ActivateFlipCoin()
{
	FGameplayTagContainer TargetTag(PGTAG_GAME_FLIPCOIN);

	if (!ASC->HasMatchingGameplayTag(PGTAG_GAME_FLIPCOIN))
	{
		ASC->TryActivateAbilitiesByTag(TargetTag);
	}
	else
	{
		ASC->CancelAbilities(&TargetTag);
	}
}

void APGGameState::ActivateSelectDeck()
{
	FGameplayTagContainer TargetTag(PGTAG_GAME_SELECTDECK);
	
	if (!ASC->HasMatchingGameplayTag(PGTAG_GAME_SELECTDECK))
	{
		ASC->TryActivateAbilitiesByTag(TargetTag);
	}
	else
	{
		ASC->CancelAbilities(&TargetTag);
	}

}

void APGGameState::ActivateGameStart()
{
	FGameplayTagContainer TargetTag(PGTAG_GAME_GAMESTART);

	if (!ASC->HasMatchingGameplayTag(PGTAG_GAME_GAMESTART))
	{
		ASC->TryActivateAbilitiesByTag(TargetTag);
	}
	else
	{
		ASC->CancelAbilities(&TargetTag);
	}
}

bool APGGameState::IsAllPlayerSelectedDeck()
{
	const TArray<APlayerState*>& Players = PlayerArray;

	for (const auto Player : Players)
	{
		bool result = false;
		APGPlayerState* PGPlayer = Cast<APGPlayerState>(Player);
		if (PGPlayer)
		{
			result = PGPlayer->GetIsSelectedDeck();
		}
		if (!result)
		{
			return false;
		}
	}
	return true;
}

bool APGGameState::IsAllPlayerReady()
{
	const TArray<APlayerState*>& Players = PlayerArray;

	for (const auto Player : Players)
	{
		bool result = false;
		APGPlayerState* PGPlayer = Cast<APGPlayerState>(Player);
		if (PGPlayer)
		{
			result = PGPlayer->GetIsGameReady();
		}
		if (!result)
		{
			return false;
		}
	}
	return true;
}

void APGGameState::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ASC->InitAbilityActorInfo(this, this);

	for (const auto& StartAbility : StartAbilities)
	{
		FGameplayAbilitySpec Spec(StartAbility);
		ASC->GiveAbility(Spec);
	}

}
