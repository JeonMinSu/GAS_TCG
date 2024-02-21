// Fill out your copyright notice in the Description page of Project Settings.


#include "PGGA_WaitForReady.h"
#include "Abilities/Tasks/AbilityTask_WaitAbilityActivate.h"
#include <PokemonGASSample/Tag/PGGameplayTag.h>

UPGGA_WaitForReady::UPGGA_WaitForReady()
{
	AbilityTags.AddTag(PGTAG_GAME_WAITFORREADY);
	//InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UPGGA_WaitForReady::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UE_LOG(LogTemp, Log, TEXT("Activate Wait For Ready"));

	UAbilityTask_WaitAbilityActivate* WaitFilpCoinTask = UAbilityTask_WaitAbilityActivate::WaitForAbilityActivate(this, PGTAG_GAME_FLIPCOIN, PGTAG_PLAYER_DRAWPRICES);
	WaitFilpCoinTask->TagRequirements.IgnoreTags.AddTag(PGTAG_PLAYER);
	WaitFilpCoinTask->TagRequirements.RequireTags.AddTag(PGTAG_GAME_STATE);

	WaitFilpCoinTask->OnActivate.AddDynamic(this, &UPGGA_WaitForReady::OnEndAbilityCallback);
}

void UPGGA_WaitForReady::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UPGGA_WaitForReady::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UPGGA_WaitForReady::OnEndAbilityCallback(UGameplayAbility* GameplayAbility)
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
