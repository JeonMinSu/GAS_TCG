// Fill out your copyright notice in the Description page of Project Settings.


#include "PGGameState.h"
#include "Component/PGGameStateASC.h"
#include "Tag/PGGameplayTag.h"
#include "PokemonGASSample.h"

APGGameState::APGGameState()
{
	ASC = CreateDefaultSubobject<UPGGameStateASC>(TEXT("ASC"));
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


void APGGameState::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (!ASC)
	{
		UE_LOG(LogPGGAS, Error, TEXT("GameState's Ability System Component is null"));
		return;
	}
	ASC->InitAbilityActorInfo(this, this);

	for (const auto& StartAbility : StartAbilities)
	{
		FGameplayAbilitySpec Spec(StartAbility);
		ASC->GiveAbility(Spec);
	}

}
