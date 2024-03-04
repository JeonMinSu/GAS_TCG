// Fill out your copyright notice in the Description page of Project Settings.


#include "GA/PGPlayerBehaviorEndAbility.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystemBlueprintLibrary.h"

void UPGPlayerBehaviorEndAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	AActor* TargetActor = UGameplayStatics::GetActorOfClass(GetWorld(), GameplayEventTargetActor);
	if (TargetActor)
	{
		FGameplayEventData Payload;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(TargetActor, EventTag, Payload);
	}
}
