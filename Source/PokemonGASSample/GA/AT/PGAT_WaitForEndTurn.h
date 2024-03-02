// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "PGAT_WaitForEndTurn.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaitForEndTurnDelegate);
UCLASS()
class POKEMONGASSAMPLE_API UPGAT_WaitForEndTurn : public UAbilityTask
{
	GENERATED_BODY()
public:
	UPGAT_WaitForEndTurn();

	UFUNCTION(BlueprintCallable, Category = "Abiltiy|Tasks", meta = (DisplayName = "WaitForEndTurn", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UPGAT_WaitForEndTurn* CreateTask(UGameplayAbility* OwningAbility);

	virtual void Activate() override;
	virtual void OnDestroy(bool AbilityEnded) override;

	UPROPERTY(BlueprintAssignable)
	FWaitForEndTurnDelegate OnCompleted;
protected:
	UFUNCTION()
	void OnPlayerEndTurnCallback(int32 PlayerIndex);

};
