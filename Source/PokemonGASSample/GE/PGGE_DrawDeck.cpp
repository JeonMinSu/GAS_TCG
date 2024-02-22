// Fill out your copyright notice in the Description page of Project Settings.


#include "PGGE_DrawDeck.h"

UPGGE_DrawDeck::UPGGE_DrawDeck()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;

	FGameplayModifierInfo DeckModifier;

	Modifiers.Add(DeckModifier);
}