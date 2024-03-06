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

UPGAT_WaitAllPlayerDone* UPGAT_WaitAllPlayerDone::CreateTask(UGameplayAbility* OwningAbility, FGameplayTag InEventTag, FGameplayTag InPlayerDoneCheckTag)
{
	UPGAT_WaitAllPlayerDone* NewTask = NewAbilityTask<UPGAT_WaitAllPlayerDone>(OwningAbility);
	NewTask->EventTag = InEventTag;
	NewTask->PlayerDoneCheckTag = InPlayerDoneCheckTag;

	return NewTask;
}

void UPGAT_WaitAllPlayerDone::Activate()
{
	Super::Activate();

	bInitialized = false;
	UAbilitySystemComponent* ASC = AbilitySystemComponent.Get();
	//DelegateHandle = ASC->AbilityEndedCallbacks.AddUObject(this, &UPGAT_WaitAllPlayerDone::AbilityEndCallback);
	DelegateHandle = ASC->RegisterGameplayTagEvent(PlayerDoneCheckTag).AddUObject(this, &UPGAT_WaitAllPlayerDone::GameplayTagCallback);

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
		SetWaitingOnAvatar();
		bInitialized = true;
	}
}

void UPGAT_WaitAllPlayerDone::OnDestroy(bool AbilityEnded)
{
	//AbilitySystemComponent.Get()->AbilityEndedCallbacks.Remove(DelegateHandle);
	AbilitySystemComponent.Get()->RegisterGameplayTagEvent(PlayerDoneCheckTag).Remove(DelegateHandle);

	Super::OnDestroy(AbilityEnded);
}

void UPGAT_WaitAllPlayerDone::GameplayTagCallback(const FGameplayTag InTag, int32 NewCount)
{
	if (NewCount == 1)
	{
		ActivationCount--;

		AbilitySystemComponent.Get()->RemoveLooseGameplayTag(InTag);

		if (bInitialized && ActivationCount == 0)
		{
			BroadcastAndEnd();
		}
	}
}

//void UPGAT_WaitAllPlayerDone::AbilityEndCallback(UGameplayAbility* EndedAbility)
//{
//	if (PlayerDoneCheckAbility == EndedAbility->GetClass())
//	{
//		ActivationCount--;
//		if (bInitialized && ActivationCount == 0)
//		{
//			BroadcastAndEnd();
//		}
//	}
//}
