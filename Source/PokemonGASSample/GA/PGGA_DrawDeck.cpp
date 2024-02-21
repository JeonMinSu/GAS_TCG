// Fill out your copyright notice in the Description page of Project Settings.


#include "PGGA_DrawDeck.h"
//#include <PokemonGASSample/Player/PGPlayerState.h>
#include <PokemonGASSample/Tag/PGGameplayTag.h>
#include "AbilitySystemComponent.h"
#include <PokemonGASSample/Attribute/PGCharacterAttributeSet.h>
#include "AbilitySystemBlueprintLibrary.h"

UPGGA_DrawDeck::UPGGA_DrawDeck()
{
	AbilityTags.AddTag(PGTAG_PLAYER_DRAWDECK);
}

void UPGGA_DrawDeck::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AActor* AvatarActor = ActorInfo->AvatarActor.Get();
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(AvatarActor);

	if (!ASC)
	{
		return;
	}

	UPGCharacterAttributeSet* AttributeSet = const_cast<UPGCharacterAttributeSet*>(ASC->GetSet<UPGCharacterAttributeSet>());

	if (!AttributeSet)
	{
		return;
	}

	if (AvatarActor)
	{
		AttributeSet->SetDeckCount(AttributeSet->GetDeckCount() - 1);
		AttributeSet->SetHandCount(AttributeSet->GetHandCount() + 1);
	}

}

void UPGGA_DrawDeck::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

}
