// Fill out your copyright notice in the Description page of Project Settings.


#include "GA/AT/Flow/PGAT_WaitAllPlayerDone.h"
#include "GameFramework/GameState.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Interface/AbilitySystem/PGTriggerAbilityInterface.h"
#include "PokemonGASSample.h"

UPGAT_WaitAllPlayerDone::UPGAT_WaitAllPlayerDone()
{
}

UPGAT_WaitAllPlayerDone* UPGAT_WaitAllPlayerDone::CreateTask(UGameplayAbility* OwningAbility, FGameplayTag InEventTag)
{
	UPGAT_WaitAllPlayerDone* NewTask = NewAbilityTask<UPGAT_WaitAllPlayerDone>(OwningAbility);
	NewTask->EventTag = InEventTag;

	return NewTask;
}

void UPGAT_WaitAllPlayerDone::Activate()
{
	Super::Activate();

	int32 TriggeredSum = 0;
	AGameStateBase* GameState = UGameplayStatics::GetGameState(Ability->GetWorld());
	for (const APlayerState* PS : GameState->PlayerArray)
	{
		const IAbilitySystemInterface* IASC = Cast<IAbilitySystemInterface>(PS);
		if (!IASC)
		{
			continue;
		}
		UAbilitySystemComponent* ASC = IASC->GetAbilitySystemComponent();
		if (!ASC)
		{
			continue;
		}
		IPGTriggerAbilityInterface* TriggerAbilitySystem = Cast<IPGTriggerAbilityInterface>(ASC);
		if (!TriggerAbilitySystem)
		{
			continue;
		}

		int32 TriggeredCount = 0;
		FGameplayEventData PayloadData;
		TriggeredCount = TriggerAbilitySystem->TriggerAbility(EventTag, &PayloadData);
		if (TriggeredCount != 1)
		{
			TriggerAbilitySystem->ResetTrackingAbility();
			UE_LOG(LogPGGAS, Error, TEXT("Triggered Ability is not one"));
			BroadcastAndEnd();
			return;
		}
		else
		{
			TriggerAbilitySystems.Add(TriggerAbilitySystem);
			DelegateMap.Add(ASC, ASC->AbilityEndedCallbacks.AddUObject(this, &UPGAT_WaitAllPlayerDone::AbilityEndCallback));
			TriggeredSum++;
		}
	}

	if (TriggeredSum == 0)
	{
		BroadcastAndEnd();
	}
	else
	{
		SetWaitingOnAvatar();
	}
	
}

void UPGAT_WaitAllPlayerDone::OnDestroy(bool AbilityEnded)
{
	for (const auto& Delegate : DelegateMap)
	{
		Delegate.Key->AbilityEndedCallbacks.Remove(Delegate.Value);
	}
	for (const auto& TAS : TriggerAbilitySystems)
	{
		TAS->ResetTrackingAbility();
	}

	Super::OnDestroy(AbilityEnded);
}

void UPGAT_WaitAllPlayerDone::AbilityEndCallback(UGameplayAbility* EndedAbility)
{
	bool AllEnded = true;

	for (const auto& TAS : TriggerAbilitySystems)
	{
		TAS->RemoveTrackingAbility(EndedAbility);
		AllEnded = AllEnded && TAS->CheckTriggeredAbilityEnd();
	}

	if (AllEnded)
	{
		BroadcastAndEnd();
	}
}
