// Fill out your copyright notice in the Description page of Project Settings.


#include "PGGA_ForceEndFlowAbility.h"
#include "AbilitySystemComponent.h"
#include "GA/PGFlowGameplayAbility.h"

void UPGGA_ForceEndFlowAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();

	// 모든 스펙을 가져와 검색
	TArray<FGameplayAbilitySpecHandle> SpecHandles;
	ASC->GetAllAbilities(SpecHandles);
	for (const FGameplayAbilitySpecHandle& SpecHandle : SpecHandles)
	{
		FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromHandle(SpecHandle);
		// 어빌리티가 플로우 어빌리티인지 캐스팅을 통한 체크
		UPGFlowGameplayAbility* FlowCheck = Cast<UPGFlowGameplayAbility>(Spec->Ability);
		if (Spec->IsActive() && FlowCheck != nullptr)
		{
			Spec->Ability->CancelAbility(SpecHandle, Spec->Ability->GetCurrentActorInfo(), Spec->Ability->GetCurrentActivationInfo(), true);
		}
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
