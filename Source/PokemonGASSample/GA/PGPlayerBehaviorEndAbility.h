// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "PGPlayerBehaviorEndAbility.generated.h"

/**
 * 
 */
UCLASS()
class POKEMONGASSAMPLE_API UPGPlayerBehaviorEndAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GAS)
	TSubclassOf<AActor> GameplayEventTargetActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GAS)
	FGameplayTag EventTag;
};
