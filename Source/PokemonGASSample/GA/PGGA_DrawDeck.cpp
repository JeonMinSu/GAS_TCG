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
			// ���⼭ ���� ���� ��Ű�� �д� ���� ���Ѿ� �ȴ�.
			PGPlayerState->DecreaseDeck(); // �� ����
			UE_LOG(LogTemp, Log, TEXT("Deck Decrease"));
		}
	}

}

void UPGGA_DrawDeck::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

}
