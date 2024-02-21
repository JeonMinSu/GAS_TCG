// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "PGAT_WaitForGameReady.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaitForGameReadyDelegate);
UCLASS()
class POKEMONGASSAMPLE_API UPGAT_WaitForGameReady : public UAbilityTask
{
	GENERATED_BODY()
public:
	UPGAT_WaitForGameReady();

	static UPGAT_WaitForGameReady* CreateTask(UGameplayAbility* OwningAbility);

	virtual void Activate() override;
	virtual void OnDestroy(bool AbilityEnded) override;

	FWaitForGameReadyDelegate OnCompleted;

protected:
	UFUNCTION()
	void OnWaitForGameReadyCallback();

};