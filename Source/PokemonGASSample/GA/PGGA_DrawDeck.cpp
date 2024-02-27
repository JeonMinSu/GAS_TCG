// Fill out your copyright notice in the Description page of Project Settings.


#include "PGGA_DrawDeck.h"
#include <PokemonGASSample/Tag/PGGameplayTag.h>
#include "AbilitySystemComponent.h"
#include <PokemonGASSample/Attribute/PGCharacterAttributeSet.h>
#include "AbilitySystemBlueprintLibrary.h"
#include <PokemonGASSample/Player/PGPlayerState.h>

UPGGA_DrawDeck::UPGGA_DrawDeck()
{
	AbilityTags.AddTag(PGTAG_PLAYER_DRAWDECK);
}

bool UPGGA_DrawDeck::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);

	return false;
}

void UPGGA_DrawDeck::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	APGPlayerState* PlayerState = CastChecked<APGPlayerState>(GetOwningActorFromActorInfo());
	UAbilitySystemComponent* ASC = PlayerState->GetAbilitySystemComponent();

	if (!ASC)
	{
		return;
	}

	UPGCharacterAttributeSet* AttributeSet = const_cast<UPGCharacterAttributeSet*>(ASC->GetSet<UPGCharacterAttributeSet>());

	if (!AttributeSet)
	{
		return;
	}

	if (AttributeSet->GetDeckCount() > 0)
	{
		APGCard* DrawCard = PlayerState->GetDeckDrawCard();
		if (DrawCard)
		{
			// 델리게이트를 사용하여 UI를 띄우는 작업이 필요.
		}
	}
	else
	{
		// 덱이 없기 때문에 죽는 판정.
	}
}

void UPGGA_DrawDeck::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

}

void UPGGA_DrawDeck::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UPGGA_DrawDeck::OnCardDrawCallback(APGCard* InCard)
{

}
