// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "PGFlowGameplayAbility.h"
#include "PGGA_DeckSelect.generated.h"

/**
 * 
 */
UCLASS()
class POKEMONGASSAMPLE_API UPGGA_DeckSelect : public UPGFlowGameplayAbility
{
	GENERATED_BODY()
public:
	UPGGA_DeckSelect();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	//UFUNCTION()
	//void OnEndAbilityCallback(UGameplayAbility* GameplayAbility);

protected:
	UFUNCTION()
	void OnDeckSelectedCallback();

};
