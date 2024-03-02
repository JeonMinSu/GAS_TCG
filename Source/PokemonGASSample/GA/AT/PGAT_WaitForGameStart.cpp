// Fill out your copyright notice in the Description page of Project Settings.


#include "PGAT_WaitForGameStart.h"
#include "Player/PGPlayerState.h"
#include "Game/PGGameState.h"

UPGAT_WaitForGameStart::UPGAT_WaitForGameStart()
{
}

UPGAT_WaitForGameStart* UPGAT_WaitForGameStart::CreateTask(UGameplayAbility* OwningAbility)
{
	UPGAT_WaitForGameStart* NewTask = NewAbilityTask<UPGAT_WaitForGameStart>(OwningAbility);
	return NewTask;
}

void UPGAT_WaitForGameStart::Activate()
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

	GameState->OnPlayerGameStartDelegate.AddDynamic(this, &UPGAT_WaitForGameStart::OnPlayerGameStartCallback);
}

void UPGAT_WaitForGameStart::OnDestroy(bool AbilityEnded)
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
		GameState->OnPlayerGameStartDelegate.RemoveDynamic(this, &UPGAT_WaitForGameStart::OnPlayerGameStartCallback);
	}
	Super::OnDestroy(AbilityEnded);
}

void UPGAT_WaitForGameStart::OnPlayerGameStartCallback()
{
	const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
	const APGGameState* GameState = Cast<APGGameState>(ActorInfo->OwnerActor);


	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnCompleted.Broadcast();
	}

	EndTask();
}
