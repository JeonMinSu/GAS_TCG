// Fill out your copyright notice in the Description page of Project Settings.


#include "GA/AT/PGAT_WaitPlayerDone.h"
#include "GameFramework/PlayerState.h" 
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

UPGAT_WaitPlayerDone::UPGAT_WaitPlayerDone()
{
}

UPGAT_WaitPlayerDone* UPGAT_WaitPlayerDone::CreateTask(UGameplayAbility* OwningAbility, TArray<APlayerState*> InPlayerStates, FGameplayTag InEventTag)
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

	for (APlayerState* PS : PlayerStates)
	{
		UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(PS);
		if (ASC == nullptr)
		{
			continue;
		}
		FDelegateHandle Handle = ASC->AbilityEndedCallbacks.AddUObject(this, &UPGAT_WaitPlayerDone::AbilityEndCheckCallback);
		Callbacks.Add(ASC, Handle);

		int32 Activated = 0;
		FGameplayEventData PayloadData;
		Activated = ASC->HandleGameplayEvent(EventTag, &PayloadData);
		
		if (Activated != 1)
		{
			UE_LOG(LogTemp, Error, TEXT("Trigger Ability Count is not valid"));
		}

		ActivationCount++;
	}

	if (ActivationCount == 0)
	{
		BroadcastAndEnd();
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
		BroadcastAndEnd();
	}
}
