// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/PGPlayerASC.h"
#include "GA/PGFlowGameplayAbility.h"
#include "Tag/PGGameplayTag.h"
#include "PokemonGASSample.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/GameStateBase.h"

void UPGPlayerASC::InitializeComponent()
{
	Super::InitializeComponent();

	GameASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(UGameplayStatics::GetGameState(GetWorld()));
	if (GameASC == nullptr)
	{
		// log
	}
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

void UPGPlayerASC::OnTagUpdated(const FGameplayTag& Tag, bool TagExists)
{
	UE_LOG(LogPGGAS, Log, TEXT("%s Player's Ability System Component tag updated!! : %s, %d"), *GetOwner()->GetName(), *Tag.ToString(), TagExists);
	OnTagUpdateCallback.ExecuteIfBound(Tag, TagExists);
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

int32 UPGPlayerASC::HandleGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload)
{
	int32 ReturnValue = Super::HandleGameplayEvent(EventTag, Payload);

	if (ReturnValue != 1)
	{
		PGGAS_LOG(LogPGGAS, Error, TEXT("Activated Ability is not one!!!"));
	}

	return ReturnValue;
}

UAbilitySystemComponent* UPGPlayerASC::GetGameASC()
{
	return GameASC;
}
