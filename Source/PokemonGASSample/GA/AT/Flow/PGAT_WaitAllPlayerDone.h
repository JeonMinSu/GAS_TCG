// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "PGAT_WaitAllPlayerDone.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAllPlayerDoneDelegate);

/**
 * 
 */
UCLASS()
class POKEMONGASSAMPLE_API UPGAT_WaitAllPlayerDone : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	UPGAT_WaitAllPlayerDone();

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "WaitAllPlayerDone", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BluprintInternalUseOnly = "TRUE"))
	static UPGAT_WaitAllPlayerDone* CreateTask(UGameplayAbility* OwningAbility, FGameplayTag InEventTag, TSubclassOf<UGameplayAbility> InPlayerDoneCheckAbility);

	virtual void Activate() override;
	virtual void OnDestroy(bool AbilityEnded) override;

	UPROPERTY(BlueprintAssignable)
	FAllPlayerDoneDelegate OnComplete;

protected:
	void AbilityEndCallback(UGameplayAbility* EndedAbility);

	void FORCEINLINE BroadcastAndEnd()
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			OnComplete.Broadcast();
		}
		EndTask();
	}

protected:
	FGameplayTag EventTag;
	TSubclassOf<UGameplayAbility> PlayerDoneCheckAbility;
	int32 ActivationCount;

	FDelegateHandle DelegateHandle;

	uint8 bInitialized : 1;
};
