// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "PGAT_WaitForDeckSelect.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaitForDeckSelectedDelegate);

/**
 * 
 */
UCLASS()
class POKEMONGASSAMPLE_API UPGAT_WaitForDeckSelect : public UAbilityTask
{
	GENERATED_BODY()
public:
	UPGAT_WaitForDeckSelect();

	static UPGAT_WaitForDeckSelect* CreateTask(UGameplayAbility* OwningAbility);

	virtual void Activate() override;
	virtual void OnDestroy(bool AbilityEnded) override;
	
	FWaitForDeckSelectedDelegate OnCompleted;

protected:
	UFUNCTION()
	void OnPlayerDeckSelectedCallback(int32 InPlayerIndex);

};
