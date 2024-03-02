// Fill out your copyright notice in the Description page of Project Settings.


#include "PGAT_WaitForEndTurn.h"
#include "Player/PGPlayerState.h"
#include "Game/PGGameState.h"
#include <Kismet/GameplayStatics.h>

UPGAT_WaitForEndTurn::UPGAT_WaitForEndTurn()
{
}

UPGAT_WaitForEndTurn* UPGAT_WaitForEndTurn::CreateTask(UGameplayAbility* OwningAbility)
{
	UPGAT_WaitForEndTurn* NewTask = NewAbilityTask<UPGAT_WaitForEndTurn>(OwningAbility);
	return NewTask;
}

void UPGAT_WaitForEndTurn::Activate()
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
	GameState->OnPlayerEndTurnDelegate.AddDynamic(this, &UPGAT_WaitForEndTurn::OnPlayerEndTurnCallback);
	SetWaitingOnAvatar();
}

void UPGAT_WaitForEndTurn::OnDestroy(bool AbilityEnded)
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
		GameState->OnPlayerEndTurnDelegate.RemoveDynamic(this, &UPGAT_WaitForEndTurn::OnPlayerEndTurnCallback);
	}

	Super::OnDestroy(AbilityEnded);
}

void UPGAT_WaitForEndTurn::OnPlayerEndTurnCallback(int32 PlayerIndex)
{
	const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
	const APGGameState* GameState = Cast<APGGameState>(ActorInfo->OwnerActor);


	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnCompleted.Broadcast();
	}

	EndTask();
}
