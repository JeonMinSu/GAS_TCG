// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "PGAT_WaitForGameStart.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaitForGameStartDelegate);
UCLASS()
class POKEMONGASSAMPLE_API UPGAT_WaitForGameStart : public UAbilityTask
{
	GENERATED_BODY()
public:
	UPGAT_WaitForGameStart();

	UFUNCTION(BlueprintCallable, Category = "Abiltiy|Tasks", meta = (DisplayName = "WaitForGameStart", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UPGAT_WaitForGameStart* CreateTask(UGameplayAbility * OwningAbility);

	virtual void Activate() override;
	virtual void OnDestroy(bool AbilityEnded) override;

	UPROPERTY(BlueprintAssignable)
	FWaitForGameStartDelegate OnCompleted;

protected:
	UFUNCTION()
	void OnPlayerGameStartCallback();
};
