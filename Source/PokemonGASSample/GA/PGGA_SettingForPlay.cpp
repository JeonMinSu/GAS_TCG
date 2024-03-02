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
	GameState->OnWaitForGameReadyDelegate.AddDynamic(this, &UPGGA_SettingForPlay::OnGameStartCallback);

	APGPlayerState* PlayerState = CastChecked<APGPlayerState>(GetOwningActorFromActorInfo());
	UAbilitySystemComponent* ASC = PlayerState->GetAbilitySystemComponent();
	if (!ASC)
	{
		return;
	}

	PlayerState->DeckShuffle();

	for (int32 i = 0; i < 7; i++)
	{
		//APGCard* DrawCard = PlayerState->GetDeckDrawCard();
		//if (DrawCard)
		//{
		//	// 델리게이트를 사용하여 UI를 띄우는 작업이 필요.
		//}
	}

	for (int32 i = 0; i < 3; i++)
	{
		//APGCard* PrizeCard = PlayerState->SetPrizeCard();
		//if (PrizeCard)
		//{
		//	// 델리게이트를 사용하여 UI를 띄우는 작업이 필요.
		//}
	}
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

	if (!PlayerState->IsGameReady())
	{
		return;
	}

	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
