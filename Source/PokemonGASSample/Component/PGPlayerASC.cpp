// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/PGPlayerASC.h"
#include "Tag/PGGameplayTag.h"

FGameplayTag UPGPlayerASC::GetNextTag(const FGameplayTagContainer& CurrentContainer)
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

bool UPGPlayerASC::ActivateNextFlow(FGameplayTag ActivationTag)
{
	FGameplayTagContainer NextActivationContainer(ActivationTag);
	return TryActivateAbilitiesByTag(NextActivationContainer);
}

int32 UPGPlayerASC::HandleGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload)
{
	int32 ReturnValue = Super::HandleGameplayEvent(EventTag, Payload);

	check(ReturnValue == 1);

	return ReturnValue;
}
