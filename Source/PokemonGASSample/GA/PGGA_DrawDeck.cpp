// Fill out your copyright notice in the Description page of Project Settings.


#include "PGGA_DrawDeck.h"
#include "../PGPlayerState.h"
#include "../Tag/PGGameplayTag.h"

UPGGA_DrawDeck::UPGGA_DrawDeck()
{
	AbilityTags.AddTag(PGTAG_PLAYER_DRAWDECK);
}

void UPGGA_DrawDeck::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	AActor* AvatarActor = ActorInfo->AvatarActor.Get();

	if (AvatarActor)
	{
		APGPlayerState* PGPlayerState = Cast<APGPlayerState>(AvatarActor);
		if (PGPlayerState)
		{
			// 여기서 덱을 감소 시키고 패는 증가 시켜야 된다.
			PGPlayerState->DecreaseDeck(); // 덱 감소
			UE_LOG(LogTemp, Log, TEXT("Deck Decrease"));
		}
	}

}

void UPGGA_DrawDeck::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

}
