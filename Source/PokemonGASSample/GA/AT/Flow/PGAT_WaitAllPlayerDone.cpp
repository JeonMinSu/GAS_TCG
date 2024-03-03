// Fill out your copyright notice in the Description page of Project Settings.


#include "GA/AT/Flow/PGAT_WaitAllPlayerDone.h"
#include "GameFramework/GameState.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "PokemonGASSample.h"

UPGAT_WaitAllPlayerDone::UPGAT_WaitAllPlayerDone()
{
	ActivationCount = 0;
}

UPGAT_WaitAllPlayerDone* UPGAT_WaitAllPlayerDone::CreateTask(UGameplayAbility* OwningAbility, FGameplayTag InEventTag, TSubclassOf<UGameplayAbility> InPlayerDoneCheckAbility)
{
	UPGAT_WaitAllPlayerDone* NewTask = NewAbilityTask<UPGAT_WaitAllPlayerDone>(OwningAbility);
	NewTask->EventTag = InEventTag;
	NewTask->PlayerDoneCheckAbility = InPlayerDoneCheckAbility;

	return NewTask;
}

void UPGAT_WaitAllPlayerDone::Activate()
{
	Super::Activate();

	AGameStateBase* GameState = UGameplayStatics::GetGameState(Ability->GetWorld());
	for (APlayerState* PS : GameState->PlayerArray)
	{
		FGameplayEventData PayloadData;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(PS, EventTag, PayloadData);
		ActivationCount++;
	}

	if (ActivationCount == 0)
	{
		BroadcastAndEnd();
	}
	else
	{
		UAbilitySystemComponent* ASC = Ability->GetAbilitySystemComponentFromActorInfo();
		DelegateMap.Add(ASC, ASC->AbilityEndedCallbacks.AddUObject(this, &UPGAT_WaitAllPlayerDone::AbilityEndCallback));

		SetWaitingOnAvatar();
	}
}

void UPGAT_WaitAllPlayerDone::OnDestroy(bool AbilityEnded)
{
	for (const auto& Delegate : DelegateMap)
	{
		Delegate.Key->AbilityEndedCallbacks.Remove(Delegate.Value);
	}

	Super::OnDestroy(AbilityEnded);
}

void UPGAT_WaitAllPlayerDone::AbilityEndCallback(UGameplayAbility* EndedAbility)
{
	if (PlayerDoneCheckAbility == EndedAbility->GetClass())
	{
		ActivationCount--;
		if (ActivationCount == 0)
		{
			BroadcastAndEnd();
		}
	}
}
