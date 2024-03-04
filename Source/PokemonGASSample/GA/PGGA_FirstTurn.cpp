// Fill out your copyright notice in the Description page of Project Settings.


#include "PGGA_FirstTurn.h"
#include <PokemonGASSample/Tag/PGGameplayTag.h>


UPGGA_FirstTurn::UPGGA_FirstTurn()
{
	//AbilityTags.AddTag(PGTAG_GAME_FIRSTTURN);
}

void UPGGA_FirstTurn::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UE_LOG(LogTemp, Log, TEXT("Activate Ability FirstTurn"));

}

void UPGGA_FirstTurn::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
	UE_LOG(LogTemp, Log, TEXT("Cancel Ability FirstTurn"));
}

void UPGGA_FirstTurn::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	UE_LOG(LogTemp, Log, TEXT("End Ability FirstTurn"));
}
