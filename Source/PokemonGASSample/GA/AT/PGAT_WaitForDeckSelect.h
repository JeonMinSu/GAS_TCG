// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "PGAT_WaitForDeckSelect.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaitForDeckSelectedDelegate);
UCLASS()
class POKEMONGASSAMPLE_API UPGAT_WaitForDeckSelect : public UAbilityTask
{
	GENERATED_BODY()
public:
	UPGAT_WaitForDeckSelect();

	UFUNCTION(BlueprintCallable, Category = "PGAbiltiy/Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UPGAT_WaitForDeckSelect* CreateTask(UGameplayAbility* OwningAbility);

	virtual void Activate() override;
	virtual void OnDestroy(bool AbilityEnded) override;
	
	UPROPERTY(BlueprintAssignable)
	FWaitForDeckSelectedDelegate OnCompleted;

protected:
	UFUNCTION()
	void OnPlayerDeckSelectedCallback();

//public:
	//FGameplayTag WithTag;
	//FGameplayTag WithoutTag;

	/// <summary>
	/// 필수 태그를 캡슐화하고 태그를 무시.
	/// </summary>
	//FGameplayTagRequirements TagRequirements;
};
