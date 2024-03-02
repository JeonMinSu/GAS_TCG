// Fill out your copyright notice in the Description page of Project Settings.


#include "GA/AT/PGAT_WaitPlayerDone.h"
#include "Player/PGPlayerState.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"

UPGAT_WaitPlayerDone::UPGAT_WaitPlayerDone()
{
}

UPGAT_WaitPlayerDone* UPGAT_WaitPlayerDone::CreateTask(UGameplayAbility* OwningAbility, TArray<APGPlayerState*> InPlayerStates, FGameplayTag InEventTag)
{
	UPGAT_WaitPlayerDone* NewTask = NewAbilityTask<UPGAT_WaitPlayerDone>(OwningAbility);
	NewTask->PlayerStates = InPlayerStates;
	NewTask->EventTag = InEventTag;

	return NewTask;
}

void UPGAT_WaitPlayerDone::Activate()
{
	Super::Activate();

	int32 ActivationCount = 0;

	for (APGPlayerState* PS : PlayerStates)
	{
		IAbilitySystemInterface* AbilityInterface = Cast<IAbilitySystemInterface>(PS);
		if (!AbilityInterface)
		{
			continue;
		}

		UAbilitySystemComponent* ASC = AbilityInterface->GetAbilitySystemComponent();
		FDelegateHandle Handle = ASC->AbilityEndedCallbacks.AddUObject(this, &UPGAT_WaitPlayerDone::AbilityEndCheckCallback);
		Callbacks.Add(ASC, Handle);

		int32 Activated = 0;
		FGameplayEventData PayloadData;
		Activated = ASC->HandleGameplayEvent(EventTag, &PayloadData);
		
		ActivationCount += Activated;
	}

	if (ActivationCount == 0)
	{
		EndTask();
	}
	else
	{
		SetWaitingOnAvatar();
		PlayerAbilityActivationCount = ActivationCount;
	}
}

void UPGAT_WaitPlayerDone::OnDestroy(bool AbilityEnded)
{
	for (const auto& CallbackData : Callbacks)
	{
		CallbackData.Key->AbilityEndedCallbacks.Remove(CallbackData.Value);
	}

	Super::OnDestroy(AbilityEnded);
}

void UPGAT_WaitPlayerDone::AbilityEndCheckCallback(UGameplayAbility* EndedAbility)
{
	if (EndedAbility->IsTriggered())
	{
		PlayerAbilityActivationCount--;
	}
	if (PlayerAbilityActivationCount <= 0)
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			OnComplete.Broadcast();
		}

		EndTask();
	}
}
