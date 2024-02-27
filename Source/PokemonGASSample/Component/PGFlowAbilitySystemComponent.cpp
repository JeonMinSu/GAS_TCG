// Fill out your copyright notice in the Description page of Project Settings.


#include "PGFlowAbilitySystemComponent.h"
#include "Tag/PGGameplayTag.h"
#include "GA/PGFlowGameplayAbility.h"

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

void UPGFlowAbilitySystemComponent::CancelAbilityWithTag(FGameplayTagContainer Tags)
{
	TArray<FGameplayAbilitySpecHandle> SpecHandles;
	FindAllAbilitiesWithTags(SpecHandles, Tags);

	for (const FGameplayAbilitySpecHandle& SpecHandle : SpecHandles)
	{
		CancelAbilityHandle(SpecHandle);
	}
}
