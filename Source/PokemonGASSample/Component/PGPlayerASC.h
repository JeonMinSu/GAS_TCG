// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Interface/AbilitySystem/PGTriggerAbilityInterface.h"
#include "Interface/AbilitySystem/PGFlowSystemInterface.h"
#include "PGPlayerASC.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FGameplayTagUpdateDelegate, const FGameplayTag&, Tag, bool, TagExists);

/**
 * 
 */
UCLASS()
class POKEMONGASSAMPLE_API UPGPlayerASC : public UAbilitySystemComponent, public IPGFlowSystemInterface
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Flow CAS")
	void EndAbilityWithTag(FGameplayTagContainer Tags);

protected:
	UFUNCTION()
	void EndAbilitySpec(FGameplayAbilitySpec& Spec);

	virtual void OnTagUpdated(const FGameplayTag& Tag, bool TagExists) override;

public:
	UPROPERTY(BlueprintReadWrite)
	FGameplayTagUpdateDelegate OnTagUpdateCallback;

	// PGFlowSystem
public:
	virtual FGameplayTag GetNextTag(const FGameplayTagContainer& CurrentContainer) override;
	virtual bool ActivateNextFlow(FGameplayTag ActivationTag) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = GAS)
	TMap<FGameplayTag, FGameplayTag> GameplayFlowTagMap;
	
public:
	virtual int32 HandleGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload) override;
};
