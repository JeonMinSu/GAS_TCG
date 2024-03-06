// Fill out your copyright notice in the Description page of Project Settings.


#include "GA/AT/Flow/PGAT_WaitOnePlayerDone.h"
#include "GameFramework/GameState.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "PokemonGASSample.h"

UPGAT_WaitOnePlayerDone::UPGAT_WaitOnePlayerDone()
{
}

UPGAT_WaitOnePlayerDone* UPGAT_WaitOnePlayerDone::CreateTask(UGameplayAbility* OwningAbility, int32 InPlayerId, FGameplayTag InEventTag, FGameplayTag InPlayerDoneCheckTag)
{
	UPGAT_WaitOnePlayerDone* NewTask = NewAbilityTask<UPGAT_WaitOnePlayerDone>(OwningAbility);
	NewTask->PlayerId = InPlayerId;
	NewTask->EventTag = InEventTag;
	NewTask->PlayerDoneCheckTag = InPlayerDoneCheckTag;

	return NewTask;
}

void UPGAT_WaitOnePlayerDone::Activate()
{
	Super::Activate();

	UAbilitySystemComponent* ASC = AbilitySystemComponent.Get();
	//DelegateHandle = ASC->AbilityEndedCallbacks.AddUObject(this, &UPGAT_WaitOnePlayerDone::AbilityEndCallback);
	DelegateHandle = ASC->RegisterGameplayTagEvent(PlayerDoneCheckTag).AddUObject(this, &UPGAT_WaitOnePlayerDone::GameplayTagCallback);

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

	FGameplayEventData PayloadData;
	PayloadData.Instigator = ASC->GetOwner();
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(PlayerState, EventTag, PayloadData);

	SetWaitingOnAvatar();
}

void UPGAT_WaitOnePlayerDone::OnDestroy(bool AbilityEnded)
{
	//Ability->GetAbilitySystemComponentFromActorInfo()->AbilityEndedCallbacks.Remove(DelegateHandle);
	AbilitySystemComponent.Get()->RegisterGameplayTagEvent(PlayerDoneCheckTag).Remove(DelegateHandle);

	Super::OnDestroy(AbilityEnded);
}

void UPGAT_WaitOnePlayerDone::GameplayTagCallback(const FGameplayTag InTag, int32 NewCount)
{
	if (NewCount == 1)
	{
		AbilitySystemComponent.Get()->RemoveLooseGameplayTag(InTag);

		BroadcastAndEnd();
	}
}

//void UPGAT_WaitOnePlayerDone::AbilityEndCallback(UGameplayAbility* EndedAbility)
//{
//	if (EndedAbility->GetClass() == PlayerDoneCheckAbility)
//	{
//		BroadcastAndEnd();
//	}
//}
