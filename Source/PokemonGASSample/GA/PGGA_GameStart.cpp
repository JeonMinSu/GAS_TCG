// Fill out your copyright notice in the Description page of Project Settings.


#include "PGGA_GameStart.h"
#include <PokemonGASSample/Tag/PGGameplayTag.h>
#include <PokemonGASSample/Tag/PGGameplayTag.h>
#include <PokemonGASSample/Game/PGGameState.h>
#include "AbilitySystemComponent.h"

UPGGA_GameStart::UPGGA_GameStart()
{
	AbilityTags.AddTag(PGTAG_GAME_GAMESTART);
}

void UPGGA_GameStart::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UE_LOG(LogTemp, Log, TEXT("Activate Game Start"));
}

void UPGGA_GameStart::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
	UE_LOG(LogTemp, Log, TEXT("Cancel Game Start"));
}

void UPGGA_GameStart::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	UE_LOG(LogTemp, Log, TEXT("End Game Start"));

	APGGameState* GameState = CastChecked<APGGameState>(CurrentActorInfo->OwnerActor.Get());
	UAbilitySystemComponent* GameASC = GameState->GetAbilitySystemComponent();

	if (GameASC)
	{
		FGameplayTagContainer TargetTag(PGTAG_GAME_FIRSTTURN);

		if (!GameASC->HasMatchingGameplayTag(PGTAG_GAME_FIRSTTURN))
		{
			GameASC->TryActivateAbilitiesByTag(TargetTag);
		}
		else
		{
			GameASC->CancelAbilities(&TargetTag);
		}
	}

}
