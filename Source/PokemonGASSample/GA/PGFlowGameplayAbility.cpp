// Fill out your copyright notice in the Description page of Project Settings.


#include "PGFlowGameplayAbility.h"
#include "Component/PGFlowAbilitySystemComponent.h"

void UPGFlowGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	UPGFlowAbilitySystemComponent* FASC = Cast<UPGFlowAbilitySystemComponent>(ActorInfo->AbilitySystemComponent.Get());
	if (FASC)
	{
		FGameplayTagContainer NextActivationContainer(FASC->GetNextTag(ActivationOwnedTags));
		FASC->TryActivateAbilitiesByTag(NextActivationContainer);
	}
}
