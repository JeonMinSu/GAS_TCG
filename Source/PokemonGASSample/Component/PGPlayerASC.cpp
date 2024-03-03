// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/PGPlayerASC.h"
#include "GA/PGFlowGameplayAbility.h"
#include "Tag/PGGameplayTag.h"

int32 UPGPlayerASC::TriggerAbility(FGameplayTag EventTag, const FGameplayEventData* Payload)
{
    int32 TriggeredAbilityCount;

	TSet<UGameplayAbility*> ExistingAbilities;

    TArray<FGameplayAbilitySpec> Specs = GetActivatableAbilities();
	for (FGameplayAbilitySpec Spec : Specs)
	{
		TArray<UGameplayAbility*> Abilities = Spec.GetAbilityInstances();
		for (UGameplayAbility* Ability : Abilities)
		{
			if (Ability->GetActorInfo().OwnerActor == this->GetOwner())
			{
				ExistingAbilities.Add(Ability);
			}
		}
	}

    TriggeredAbilityCount = HandleGameplayEvent(EventTag, Payload);

	for (FGameplayAbilitySpec Spec : Specs)
	{
		TArray<UGameplayAbility*> Abilities = Spec.GetAbilityInstances();
		for (UGameplayAbility* Ability : Abilities)
		{
			if (Ability->GetActorInfo().OwnerActor == this->GetOwner() && !ExistingAbilities.Contains(Ability))
			{
				TriggeredAbilities.Add(Ability);
			}
		}
	}

    return TriggeredAbilityCount;
}

bool UPGPlayerASC::CheckTriggeredAbilityEnd()
{
    return (TriggeredAbilities.Num() == 0);
}

TArray<UGameplayAbility*> UPGPlayerASC::GetTrackingAbilities() const
{
    return TriggeredAbilities;
}

void UPGPlayerASC::RemoveTrackingAbility(UGameplayAbility* RemovingAbility)
{
	TriggeredAbilities.Remove(RemovingAbility);
}

void UPGPlayerASC::ResetTrackingAbility()
{
	TriggeredAbilities.Reset();
}

void UPGPlayerASC::EndAbilityWithTag(FGameplayTagContainer Tags)
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

void UPGPlayerASC::EndAbilitySpec(FGameplayAbilitySpec& Spec)
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
