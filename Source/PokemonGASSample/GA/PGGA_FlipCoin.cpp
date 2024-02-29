// Fill out your copyright notice in the Description page of Project Settings.


#include "PGGA_FlipCoin.h"
#include "AbilitySystemComponent.h"
#include <PokemonGASSample/Tag/PGGameplayTag.h>
#include <Kismet/KismetMathLibrary.h>
#include <Kismet/GameplayStatics.h>
#include <PokemonGASSample/Player/PGPlayerState.h>
#include <AbilitySystemBlueprintLibrary.h>

UPGGA_FlipCoin::UPGGA_FlipCoin()
{
	AbilityTags.AddTag(PGTAG_GAME_FLIPCOIN);
}

void UPGGA_FlipCoin::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UE_LOG(LogTemp, Log, TEXT("Activate Ability Flip Coin"));
}

void UPGGA_FlipCoin::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
	UE_LOG(LogTemp, Log, TEXT("Cancel Ability Flip Coin"));

}

void UPGGA_FlipCoin::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	UE_LOG(LogTemp, Log, TEXT("End Ability Flip Coin"));

	//UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	//if (ASC)
	//{
	//	FGameplayTagContainer TargetTag(PGTAG_GAME_WAITFORREADY);
	//	if (!ASC->HasMatchingGameplayTag(PGTAG_GAME_WAITFORREADY))
	//	{ 
	//		ASC->TryActivateAbilitiesByTag(TargetTag);
	//	}
	//	else
	//	{
	//		ASC->CancelAbilities(&TargetTag);
	//	}
	//}
}
