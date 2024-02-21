// Fill out your copyright notice in the Description page of Project Settings.


#include "PGAT_WaitForDeckSelect.h"
#include <PokemonGASSample/Game/PGGameState.h>
#include <Kismet/KismetArrayLibrary.h>

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

	if (!AbilitySystemComponent.IsValid())
	{
		return;
	}

	APGGameState* GameState = CastChecked<APGGameState>(GetAvatarActor());
	GameState->OnPlayerSelectedDeck.AddDynamic(this, &UPGAT_WaitForDeckSelect::OnPlayerDeckSelectedCallback);

	SetWaitingOnAvatar();
}

void UPGAT_WaitForDeckSelect::OnDestroy(bool AbilityEnded)
{
	if (AbilitySystemComponent.IsValid())
	{
		APGGameState* GameState = CastChecked<APGGameState>(GetAvatarActor());
		GameState->OnPlayerSelectedDeck.RemoveDynamic(this, &UPGAT_WaitForDeckSelect::OnPlayerDeckSelectedCallback);
	}
	Super::OnDestroy(AbilityEnded);
}

void UPGAT_WaitForDeckSelect::OnPlayerDeckSelectedCallback()
{
	APGGameState* GameState = CastChecked<APGGameState>(GetAvatarActor());

	if (!GameState->IsAllPlayerSelectedDeck())
	{
		return;
	}

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnCompleted.Broadcast();
		GameState->ActivateFlipCoin();
	}
}
