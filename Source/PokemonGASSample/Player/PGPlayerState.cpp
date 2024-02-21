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

void APGPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();;
}

void APGPlayerState::BeginPlay()
{
	Super::BeginPlay();
}