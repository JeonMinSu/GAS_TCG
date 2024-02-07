// Fill out your copyright notice in the Description page of Project Settings.


#include "PGPlayerState.h"
#include "AbilitySystemComponent.h"
#include "Tag/PGGameplayTag.h"
#include "Abilities/GameplayAbility.h"

APGPlayerState::APGPlayerState()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	MaxDeckCount = 15;
}

UAbilitySystemComponent* APGPlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}

void APGPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// 실제 조정하고 관리하는 실제 작업이 이뤄나고 있는 Actor
	// 비주얼로 처리해주는 Actor
	DeckCount = MaxDeckCount;
	ASC->InitAbilityActorInfo(this, this);

	for (const auto& StartAbility : StartAbilities)
	{
		FGameplayAbilitySpec DeckSpec(StartAbility);
		ASC->GiveAbility(DeckSpec);
	}
}

void APGPlayerState::BeginPlay()
{
	Super::BeginPlay();

	FGameplayTagContainer TargetTag(PGTAG_PLAYER_DRAWDECK);

	if (!ASC->HasMatchingGameplayTag(PGTAG_PLAYER_DRAWDECK))
	{
		ASC->TryActivateAbilitiesByTag(TargetTag);
	}
	else
	{
		ASC->CancelAbilities(&TargetTag);
	}
}