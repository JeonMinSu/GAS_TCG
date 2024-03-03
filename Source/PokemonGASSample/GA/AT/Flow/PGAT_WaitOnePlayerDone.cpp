// Fill out your copyright notice in the Description page of Project Settings.


#include "GA/AT/Flow/PGAT_WaitOnePlayerDone.h"
#include "GameFramework/GameState.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Interface/AbilitySystem/PGTriggerAbilityInterface.h"
#include "PokemonGASSample.h"

UPGAT_WaitOnePlayerDone::UPGAT_WaitOnePlayerDone()
{
}

UPGAT_WaitOnePlayerDone* UPGAT_WaitOnePlayerDone::CreateTask(UGameplayAbility* OwningAbility, int32 InPlayerId, FGameplayTag InEventTag)
{
	UPGAT_WaitOnePlayerDone* NewTask = NewAbilityTask<UPGAT_WaitOnePlayerDone>(OwningAbility);
	NewTask->PlayerId = InPlayerId;
	NewTask->EventTag = InEventTag;

	return NewTask;
}

void UPGAT_WaitOnePlayerDone::Activate()
{
	Super::Activate();

	int32 TriggeredSum = 0;
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

	const IAbilitySystemInterface* IASC = Cast<IAbilitySystemInterface>(PlayerState);
	if (IASC)
	{
		PlayerAbilitySystemComponent = IASC->GetAbilitySystemComponent();
		if (PlayerAbilitySystemComponent)
		{
			PlayerTriggerAbilitySystems = Cast<IPGTriggerAbilityInterface>(PlayerAbilitySystemComponent);
			if (PlayerTriggerAbilitySystems)
			{
				int32 TriggeredCount = 0;
				FGameplayEventData PayloadData;
				TriggeredCount = PlayerTriggerAbilitySystems->TriggerAbility(EventTag, &PayloadData);

				if (TriggeredCount != 1)
				{
					PlayerTriggerAbilitySystems->ResetTrackingAbility();
					UE_LOG(LogPGGAS, Error, TEXT("Triggered Ability is not one"));
					BroadcastAndEnd();
					return;
				}

				DelegateHandle = PlayerAbilitySystemComponent->AbilityEndedCallbacks.AddUObject(this, &UPGAT_WaitOnePlayerDone::AbilityEndCallback);
			}
		}
	}

	SetWaitingOnAvatar();
}

void UPGAT_WaitOnePlayerDone::OnDestroy(bool AbilityEnded)
{
	PlayerAbilitySystemComponent->AbilityEndedCallbacks.Remove(DelegateHandle);
	PlayerTriggerAbilitySystems->ResetTrackingAbility();

	Super::OnDestroy(AbilityEnded);
}

void UPGAT_WaitOnePlayerDone::AbilityEndCallback(UGameplayAbility* EndedAbility)
{
	PlayerTriggerAbilitySystems->RemoveTrackingAbility(EndedAbility);
	if (PlayerTriggerAbilitySystems->CheckTriggeredAbilityEnd())
	{
		BroadcastAndEnd();
	}
}
