// Fill out your copyright notice in the Description page of Project Settings.


#include "GA/PGPlayerBehaviorEndAbility.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Component/PGPlayerASC.h"
#include "PokemonGASSample.h"

void UPGPlayerBehaviorEndAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	UE_LOG(LogPGGAS, Log, TEXT("PlayerBehaviorEnd Ability With Tag : %s On %s Activated"), *ActivationOwnedTags.ToString(), *ActorInfo->OwnerActor->GetName());
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UPGPlayerBehaviorEndAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	/*AActor* TargetActor = UGameplayStatics::GetActorOfClass(GetWorld(), GameplayEventTargetActor);
	if (TargetActor)
	{
		FGameplayEventData Payload;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(TargetActor, EventTag, Payload);
	}*/

	UPGPlayerASC* PlayerASC = Cast<UPGPlayerASC>(ActorInfo->AbilitySystemComponent);
	if (PlayerASC == nullptr)
	{
		// log
		return;
	}

	PlayerASC->GetGameASC()->AddLooseGameplayTag(PlayerASC->GetPlayerBehaviorDoneTag());
	if (bReplicateEndAbility)
	{
		PlayerASC->GetGameASC()->AddReplicatedLooseGameplayTag(PlayerASC->GetPlayerBehaviorDoneTag());
	}

	UE_LOG(LogPGGAS, Log, TEXT("PlayerBehaviorEnd Ability With Tag : %s On %s Ended"), *ActivationOwnedTags.ToString(), *ActorInfo->OwnerActor->GetName());
}
