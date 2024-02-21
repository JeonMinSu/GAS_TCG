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

	APGGameState* GameState = CastChecked<APGGameState>(GetAvatarActor());
	GameState->OnPlayerSelectDeck.AddDynamic(this, &UPGAT_WaitForDeckSelect::OnPlayerDeckSelectedCallback);

	SetWaitingOnAvatar();
}

void UPGAT_WaitForDeckSelect::OnDestroy(bool AbilityEnded)
{
	APGGameState* GameState = CastChecked<APGGameState>(GetAvatarActor());
	
	GameState->OnPlayerSelectDeck.RemoveDynamic(this, &UPGAT_WaitForDeckSelect::OnPlayerDeckSelectedCallback);
	Super::OnDestroy(AbilityEnded);
}

void UPGAT_WaitForDeckSelect::OnPlayerDeckSelectedCallback(int32 InPlayerIndex)
{
	APGGameState* GameState = Cast<APGGameState>(GetAvatarActor());

	if (!GameState)
	{
		return;
	}

	if (!GameState->TrySetIsPlayerSelectDeck(InPlayerIndex, true))
	{
		return;
	}

	if (!GameState->IsPlayerSelectedDeck())
	{
		return;
	}

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnCompleted.Broadcast();
		GameState->ActivateFlipCoin();
	}
}
