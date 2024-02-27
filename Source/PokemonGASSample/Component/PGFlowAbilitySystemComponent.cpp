// Fill out your copyright notice in the Description page of Project Settings.


#include "PGFlowAbilitySystemComponent.h"
#include "Tag/PGGameplayTag.h"

FGameplayTag UPGFlowAbilitySystemComponent::GetNextTag(const FGameplayTagContainer& CurrentContainer)
{
	if (HasMatchingGameplayTag(PGTAG_GAME_STATE_NONE))
	{
		return PGTAG_GAME_STATE_NONE;
	}

	for (const auto& Tag : GameplayFlowTagMap)
	{
		if (CurrentContainer.HasTagExact(Tag.Key))
		{
			return Tag.Value;
		}
	}

	return PGTAG_GAME_STATE_NONE;
}
