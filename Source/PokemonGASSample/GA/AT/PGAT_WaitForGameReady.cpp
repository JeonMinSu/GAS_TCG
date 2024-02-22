// Fill out your copyright notice in the Description page of Project Settings.


#include "PGAT_WaitForGameReady.h"
#include <PokemonGASSample/Game/PGGameState.h>
#include <Kismet/GameplayStatics.h>
#include <PokemonGASSample/Game/PGGameMode.h>

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

	if (!AbilitySystemComponent.IsValid())
	{
		return;
	}

	APGGameState* GameState = CastChecked<APGGameState>(GetAvatarActor());
	GameState->OnWaitForGameReady.AddDynamic(this, &UPGAT_WaitForGameReady::OnWaitForGameReadyCallback);

	SetWaitingOnAvatar();
}

void UPGAT_WaitForGameReady::OnDestroy(bool AbilityEnded)
{
	if (AbilitySystemComponent.IsValid())
	{
		APGGameState* GameState = CastChecked<APGGameState>(GetAvatarActor());
		GameState->OnWaitForGameReady.RemoveDynamic(this, &UPGAT_WaitForGameReady::OnWaitForGameReadyCallback);
	}
	Super::OnDestroy(AbilityEnded);
}

void UPGAT_WaitForGameReady::OnWaitForGameReadyCallback()
{
	APGGameState* GameState = CastChecked<APGGameState>(GetAvatarActor());

	if (!GameState->IsAllPlayerReady())
	{
		return;
	}

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnCompleted.Broadcast();
	}
}
