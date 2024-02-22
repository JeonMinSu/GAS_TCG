// Fill out your copyright notice in the Description page of Project Settings.


#include "PGGA_WaitForReady.h"
#include <Kismet/GameplayStatics.h>
#include "AT/PGAT_WaitForGameReady.h"
#include "AbilitySystemComponent.h"
#include <PokemonGASSample/Tag/PGGameplayTag.h>
#include <PokemonGASSample/Game/PGGameMode.h>
#include <PokemonGASSample/Game/PGGameState.h>
#include <PokemonGASSample/Player/PGPlayerState.h>

UPGGA_WaitForReady::UPGGA_WaitForReady()
{
	AbilityTags.AddTag(PGTAG_GAME_WAITFORREADY);
	//InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

bool UPGGA_WaitForReady::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	bool bResult = Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
	if (!bResult)
	{
		return false;
	}
	return true;
}

void UPGGA_WaitForReady::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UE_LOG(LogTemp, Log, TEXT("Activate Wait For Ready"));
	
	UPGAT_WaitForGameReady* WaitForGameReady = UPGAT_WaitForGameReady::CreateTask(this);
	WaitForGameReady->OnCompleted.AddDynamic(this, &UPGGA_WaitForReady::OnGameReadyCallback);
	WaitForGameReady->ReadyForActivation();

	const UWorld* World = GetWorld();

	int32 PlayerNum = UGameplayStatics::GetNumPlayerStates(World);

	for (int32 i = 0; i < PlayerNum; i++)
	{
		APGPlayerState* PlayerState = CastChecked<APGPlayerState>(UGameplayStatics::GetPlayerState(World, i));
		UAbilitySystemComponent* PlayerASC = PlayerState->GetAbilitySystemComponent();
		if (!PlayerASC)
		{
			continue;
		}

		FGameplayTagContainer TargetTag(PGTAG_PLAYER_SETTINGFORPLAY);
		if (!PlayerASC->HasMatchingGameplayTag(PGTAG_PLAYER_SETTINGFORPLAY))
		{
			PlayerASC->TryActivateAbilitiesByTag(TargetTag);
		}
		else
		{
			PlayerASC->CancelAbilities(&TargetTag);
		}
	}

}

void UPGGA_WaitForReady::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UPGGA_WaitForReady::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	UE_LOG(LogTemp, Log, TEXT("End Wait For Ready"));
}

void UPGGA_WaitForReady::OnGameReadyCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);



	//APGGameState* GameState = CastChecked<APGGameState>(CurrentActorInfo->AvatarActor.Get());
	//Cast<APGGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->StartMatch();
	//GameState->ActivateGameStart();
}
