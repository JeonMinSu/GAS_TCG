// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "PGAT_WaitUIConfirm.generated.h"

/**
 * 
 */
UCLASS()
class POKEMONGASSAMPLE_API UPGAT_WaitUIConfirm : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	UPGAT_WaitUIConfirm();

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "WaitUIConfirm", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BluprintInternalUseOnly = "TRUE"))
	static UPGAT_WaitUIConfirm* CreateTask(UGameplayAbility* OwningAbility, FName TaskInstanceName);
};
