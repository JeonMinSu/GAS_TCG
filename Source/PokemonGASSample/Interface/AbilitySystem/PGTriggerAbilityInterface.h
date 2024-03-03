// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AbilitySystemComponent.h"
#include "PGTriggerAbilityInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPGTriggerAbilityInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class POKEMONGASSAMPLE_API IPGTriggerAbilityInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual int32 TriggerAbility(FGameplayTag EventTag, const FGameplayEventData* Payload) = 0;
	virtual bool CheckTriggeredAbilityEnd() = 0;
	virtual TArray<UGameplayAbility*> GetTrackingAbilities() const = 0;
	virtual void RemoveTrackingAbility(UGameplayAbility* RemovingAbility) = 0;
	virtual void ResetTrackingAbility() = 0;
};
