// Fill out your copyright notice in the Description page of Project Settings.


#include "PGFlowGameplayAbility.h"
#include "PokemonGASSample.h"
#include "Interface/AbilitySystem/PGFlowSystemInterface.h"
#include "AbilitySystemComponent.h"

void UPGFlowGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	UE_LOG(LogPGGAS, Log, TEXT("Flow Ability With Tag : %s On %s Activated"), *ActivationOwnedTags.ToString(), *ActorInfo->OwnerActor->GetName());
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UPGFlowGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	IPGFlowSystemInterface* FlowSystem = Cast<IPGFlowSystemInterface>(ActorInfo->AbilitySystemComponent.Get());
	if (FlowSystem && FlowSystem->ActivateNextFlow(FlowSystem->GetNextTag(ActivationOwnedTags)))
	{
		UE_LOG(LogPGGAS, Log, TEXT("Flow Ability With Tag : %s On %s Ended"), *ActivationOwnedTags.ToString(), *ActorInfo->OwnerActor->GetName());
	}
}
