// Fill out your copyright notice in the Description page of Project Settings.


#include "PGGA_SettingForPlay.h"
#include <PokemonGASSample/Tag/PGGameplayTag.h>
#include <PokemonGASSample/Player/PGPlayerState.h>
#include <PokemonGASSample/Attribute/PGCharacterAttributeSet.h>
#include <PokemonGASSample/Game/PGGameState.h>
#include <Kismet/GameplayStatics.h>

UPGGA_SettingForPlay::UPGGA_SettingForPlay()
{
	AbilityTags.AddTag(PGTAG_PLAYER_SETTINGFORPLAY);
}

bool UPGGA_SettingForPlay::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	bool bResult = Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
	if (!bResult)
	{
		return false;
	}

	return true;
}

void UPGGA_SettingForPlay::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UE_LOG(LogTemp, Log, TEXT("Acitvate Setting for play"));

	APGGameState* GameState = CastChecked<APGGameState>(UGameplayStatics::GetGameState(GetWorld()));
	GameState->OnWaitForGameReady.AddDynamic(this, &UPGGA_SettingForPlay::OnGameStartCallback);

	APGPlayerState* PlayerState = CastChecked<APGPlayerState>(GetOwningActorFromActorInfo());
	UAbilitySystemComponent* ASC = PlayerState->GetAbilitySystemComponent();
	if (!ASC)
	{
		return;
	}

	PlayerState->DeckShuffle();

	UPGCharacterAttributeSet* AttributeSet = const_cast<UPGCharacterAttributeSet*>(ASC->GetSet<UPGCharacterAttributeSet>());

	if (!AttributeSet)
	{
		return;
	}
	
	AttributeSet->SetDeckCount(AttributeSet->GetDeckCount() - 7);
	AttributeSet->SetHandCount(AttributeSet->GetHandCount() + 7);

}

void UPGGA_SettingForPlay::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
	UE_LOG(LogTemp, Log, TEXT("Cancel Setting for play"));
}

void UPGGA_SettingForPlay::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	UE_LOG(LogTemp, Log, TEXT("End Setting for play"));
}

void UPGGA_SettingForPlay::OnGameStartCallback()
{
	APGPlayerState* PlayerState = Cast<APGPlayerState>(CurrentActorInfo->OwnerActor.Get());

	if (!PlayerState->GetIsGameReady())
	{
		return;
	}

	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
