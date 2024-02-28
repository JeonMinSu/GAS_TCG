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
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;
	FindAllAbilitiesWithTags(AbilitySpecHandles, Tags);

	for (const FGameplayAbilitySpecHandle& AbilitySpecHandle : AbilitySpecHandles)
	{
		CancelAbilityHandle(AbilitySpecHandle);
	}
}

void UPGFlowAbilitySystemComponent::EndAbilityWithTag(FGameplayTagContainer Tags)
{
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;
	FindAllAbilitiesWithTags(AbilitySpecHandles, Tags);

	for (const FGameplayAbilitySpecHandle& AbilitySpecHandle : AbilitySpecHandles)
	{
		for (FGameplayAbilitySpec& Spec : ActivatableAbilities.Items)
		{
			if (Spec.Handle == AbilitySpecHandle)
			{
				EndAbilitySpec(Spec);
				return;
			}
		}
	}
}

void UPGFlowAbilitySystemComponent::EndAbilitySpec(FGameplayAbilitySpec& Spec)
{
	FGameplayAbilityActorInfo* ActorInfo = AbilityActorInfo.Get();

	if (Spec.Ability->GetInstancingPolicy() != EGameplayAbilityInstancingPolicy::NonInstanced)
	{
		TArray<UGameplayAbility*> AbilitiesToEnd = Spec.GetAbilityInstances();
		for (UGameplayAbility* InstanceAbility : AbilitiesToEnd)
		{
			UPGFlowGameplayAbility* FlowAbility = Cast<UPGFlowGameplayAbility>(InstanceAbility);
			if (FlowAbility)
			{
				bool bReplicatedEndAbility = true;
				bool bWasCancelled = false;
				FlowAbility->EndAbility(Spec.Handle, ActorInfo, InstanceAbility->GetCurrentActivationInfo(), bReplicatedEndAbility, bWasCancelled);
			}
		}
	}
}
