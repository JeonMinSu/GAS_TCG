// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "PGAT_WaitPlayerDone.generated.h"

class APlayerState;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaitPlayerDoneDelegate);

/**
 * 
 */
UCLASS()
class POKEMONGASSAMPLE_API UPGAT_WaitPlayerDone : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	UPGAT_WaitPlayerDone();

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "WaitPlayerDone", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BluprintInternalUseOnly = "TRUE"))
	static UPGAT_WaitPlayerDone* CreateTask(UGameplayAbility* OwningAbility, TArray<APlayerState*> InPlayerStates, FGameplayTag InEventTag);

	virtual void Activate() override;
	virtual void OnDestroy(bool AbilityEnded) override;

	UPROPERTY(BlueprintAssignable)
	FWaitPlayerDoneDelegate OnComplete;

protected:
	void AbilityEndCheckCallback(UGameplayAbility* EndedAbility);

	void FORCEINLINE BroadcastAndEnd()
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			OnComplete.Broadcast();
		}
		EndTask();
	}

protected:
	TArray<TObjectPtr<APlayerState>> PlayerStates;
	FGameplayTag EventTag;

	TMap<TObjectPtr<UAbilitySystemComponent>, FDelegateHandle> Callbacks;

	int32 PlayerAbilityActivationCount;
};
