// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "PGAT_WaitOnePlayerDone.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnePlayerDoneDelegate);

/**
 * 
 */
UCLASS()
class POKEMONGASSAMPLE_API UPGAT_WaitOnePlayerDone : public UAbilityTask
{
	GENERATED_BODY()

public:
	UPGAT_WaitOnePlayerDone();

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "WaitOnePlayerDone", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BluprintInternalUseOnly = "TRUE"))
	static UPGAT_WaitOnePlayerDone* CreateTask(UGameplayAbility* OwningAbility, int32 InPlayerId, FGameplayTag InEventTag, FGameplayTag InPlayerDoneCheckTag);

	virtual void Activate() override;
	virtual void OnDestroy(bool AbilityEnded) override;

	UPROPERTY(BlueprintAssignable)
	FOnePlayerDoneDelegate OnComplete;

protected:
	//void AbilityEndCallback(UGameplayAbility* EndedAbility);
	void GameplayTagCallback(const FGameplayTag InTag, int32 NewCount);

	void BroadcastAndEnd();

protected:
	int32 PlayerId;
	FGameplayTag EventTag;
	FGameplayTag PlayerDoneCheckTag;
	//TSubclassOf<UGameplayAbility> PlayerDoneCheckAbility;

	FDelegateHandle DelegateHandle;
};
