// Fill out your copyright notice in the Description page of Project Settings.


#include "PGAT_WaitForGameReady.h"
#include "Player/PGPlayerState.h"
#include "Game/PGGameState.h"
#include <Kismet/GameplayStatics.h>

UPGAT_WaitForGameReady::UPGAT_WaitForGameReady()
{
}

UPGAT_WaitForGameReady* UPGAT_WaitForGameReady::CreateTask(UGameplayAbility* OwningAbility)
{
	UPGAT_WaitForGameReady* NewTask = NewAbilityTask<UPGAT_WaitForGameReady>(OwningAbility);
	return NewTask;
}

void UPGAT_WaitForGameReady::Activate()
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

	GameState->OnWaitForGameReadyDelegate.AddDynamic(this, &UPGAT_WaitForGameReady::OnWaitForGameReadyCallback);
	SetWaitingOnAvatar();
}

void UPGAT_WaitForGameReady::OnDestroy(bool AbilityEnded)
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
		GameState->OnWaitForGameReadyDelegate.RemoveDynamic(this, &UPGAT_WaitForGameReady::OnWaitForGameReadyCallback);
	}
	Super::OnDestroy(AbilityEnded);
}

void UPGAT_WaitForGameReady::OnWaitForGameReadyCallback()
{
	const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
	const APGGameState* GameState = Cast<APGGameState>(ActorInfo->OwnerActor);

	for (const auto PlayerState : GameState->PlayerArray)
	{
		APGPlayerState* PGPlayerState = Cast<APGPlayerState>(PlayerState);
		if (!PGPlayerState)
		{
			return;
		}
		if (!PGPlayerState->IsGameReady())
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
