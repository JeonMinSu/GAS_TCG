// Fill out your copyright notice in the Description page of Project Settings.


#include "PGAT_WaitForDeckSelect.h"
#include "Player/PGPlayerState.h"
#include "Game/PGGameState.h"
#include "PokemonGASSample.h"

UPGAT_WaitForDeckSelect::UPGAT_WaitForDeckSelect()
{
}

UPGAT_WaitForDeckSelect* UPGAT_WaitForDeckSelect::CreateTask(UGameplayAbility* OwningAbility)
{
	UPGAT_WaitForDeckSelect* NewTask = NewAbilityTask<UPGAT_WaitForDeckSelect>(OwningAbility);
	return NewTask;
}

void UPGAT_WaitForDeckSelect::Activate()
{
	Super::Activate();

	if (!Ability)
	{
		return;
	}

	if (!AbilitySystemComponent.IsValid())
	{
		return;
	}

	const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
	APGGameState* GameState = Cast<APGGameState>(ActorInfo->OwnerActor);
	if (!GameState)
	{
		return;
	}
	GameState->OnPlayerSelectedDeckDelegate.AddDynamic(this, &UPGAT_WaitForDeckSelect::OnPlayerDeckSelectedCallback);
	SetWaitingOnAvatar();
}

void UPGAT_WaitForDeckSelect::OnDestroy(bool AbilityEnded)
{
	if (!Ability)
	{
		return;
	}

	if (!AbilitySystemComponent.IsValid())
	{
		return;
	}

	const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
	APGGameState* GameState = Cast<APGGameState>(ActorInfo->OwnerActor);
	if (GameState)
	{
		GameState->OnPlayerSelectedDeckDelegate.RemoveDynamic(this, &UPGAT_WaitForDeckSelect::OnPlayerDeckSelectedCallback);
	}
	Super::OnDestroy(AbilityEnded);
}

void UPGAT_WaitForDeckSelect::OnPlayerDeckSelectedCallback(/*APlayerState* PlayerState*/)
{	
	//if (!PlayerState)
	//{
	//	return;
	//}

	//const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
	//APGGameState* GameState = Cast<APGGameState>(ActorInfo->OwnerActor);

	//APGPlayerState* PGPlayerState = Cast<APGPlayerState>(PlayerState);
	//if (PGPlayerState)
	//{
	//	PGGAS_LOG(LogPGGAS, Log, TEXT("Player State : %d"), PlayerState->GetPlayerId());
	//}

	const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
	APGGameState* GameState = Cast<APGGameState>(ActorInfo->OwnerActor);
	for (const auto PlayerState : GameState->PlayerArray)
	{
		APGPlayerState* PGPlayerState = Cast<APGPlayerState>(PlayerState);
		if (!PGPlayerState)
		{
			return;
		}
		if (!PGPlayerState->IsSelectedDeck())
		{
			return;
		}
	}

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnCompleted.Broadcast();
	}

	EndTask();
}
