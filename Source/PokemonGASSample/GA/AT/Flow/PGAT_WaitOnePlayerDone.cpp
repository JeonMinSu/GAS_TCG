// Fill out your copyright notice in the Description page of Project Settings.


#include "GA/AT/Flow/PGAT_WaitOnePlayerDone.h"
#include "GameFramework/GameState.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "PokemonGASSample.h"

UPGAT_WaitOnePlayerDone::UPGAT_WaitOnePlayerDone()
{
}

UPGAT_WaitOnePlayerDone* UPGAT_WaitOnePlayerDone::CreateTask(UGameplayAbility* OwningAbility, int32 InPlayerId, FGameplayTag InEventTag, TSubclassOf<UGameplayAbility> InPlayerDoneCheckAbility)
{
	UPGAT_WaitOnePlayerDone* NewTask = NewAbilityTask<UPGAT_WaitOnePlayerDone>(OwningAbility);
	NewTask->PlayerId = InPlayerId;
	NewTask->EventTag = InEventTag;
	NewTask->PlayerDoneCheckAbility = InPlayerDoneCheckAbility;

	return NewTask;
}

void UPGAT_WaitOnePlayerDone::Activate()
{
	Super::Activate();

	DelegateHandle = Ability->GetAbilitySystemComponentFromActorInfo()->AbilityEndedCallbacks.AddUObject(this, &UPGAT_WaitOnePlayerDone::AbilityEndCallback);

	AGameStateBase* GameState = UGameplayStatics::GetGameState(Ability->GetWorld());
	APlayerState* PlayerState = nullptr;
	for (APlayerState* PS : GameState->PlayerArray)
	{
		if (PS->GetPlayerId() == PlayerId)
		{
			PlayerState = PS;
		}
	}
	if (PlayerState == nullptr)
	{
		UE_LOG(LogPGGAS, Error, TEXT("%d ID Player is not exist"), PlayerId);
	}

	FGameplayEventData PayloadData;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(PlayerState, EventTag, PayloadData);

	SetWaitingOnAvatar();
}

void UPGAT_WaitOnePlayerDone::OnDestroy(bool AbilityEnded)
{
	Ability->GetAbilitySystemComponentFromActorInfo()->AbilityEndedCallbacks.Remove(DelegateHandle);

	Super::OnDestroy(AbilityEnded);
}

void UPGAT_WaitOnePlayerDone::AbilityEndCallback(UGameplayAbility* EndedAbility)
{
	if (EndedAbility->GetClass() == PlayerDoneCheckAbility)
	{
		BroadcastAndEnd();
	}
}
