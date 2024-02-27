// Fill out your copyright notice in the Description page of Project Settings.


#include "PGGA_DeckSelect.h"
#include "AT/PGAT_WaitForDeckSelect.h"
#include <PokemonGASSample/Tag/PGGameplayTag.h>
#include <PokemonGASSample/Game/PGGameState.h>

UPGGA_DeckSelect::UPGGA_DeckSelect()
{
	AbilityTags.AddTag(PGTAG_GAME_SELECTDECK);
	//InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UPGGA_DeckSelect::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UE_LOG(LogTemp, Log, TEXT("Activate Ability Deck Select"));

	UPGAT_WaitForDeckSelect* WaitForDeckSelectTask = UPGAT_WaitForDeckSelect::CreateTask(this);
	WaitForDeckSelectTask->OnCompleted.AddDynamic(this, &UPGGA_DeckSelect::OnDeckSelectedCallback);
	WaitForDeckSelectTask->ReadyForActivation();
}

void UPGGA_DeckSelect::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
	UE_LOG(LogTemp, Log, TEXT("Cancel Ability Deck Select"));
}

void UPGGA_DeckSelect::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	UE_LOG(LogTemp, Log, TEXT("End Ability Deck Select"));
}

void UPGGA_DeckSelect::OnDeckSelectedCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);

	APGGameState* GameState = CastChecked<APGGameState>(CurrentActorInfo->AvatarActor.Get());
	GameState->ActivateFlipCoin();
}