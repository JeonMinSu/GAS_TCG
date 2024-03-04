// Fill out your copyright notice in the Description page of Project Settings.


#include "PGGameState.h"
#include "Component/PGGameStateASC.h"
#include "Tag/PGGameplayTag.h"
#include "PokemonGASSample.h"

APGGameState::APGGameState()
{
	this->ASC = nullptr;
	this->ASC = CreateDefaultSubobject<UPGGameStateASC>(TEXT("GameStateASC"));
	this->ASC->SetIsReplicated(true);

	check(ASC);
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
	ASC->InitAbilityActorInfo(this, this);

	for (const auto& StartAbility : StartAbilities)
	{
		FGameplayAbilitySpec Spec(StartAbility);
		ASC->GiveAbility(Spec);
	}

}

void APGGameState::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	check(this->ASC);
}
