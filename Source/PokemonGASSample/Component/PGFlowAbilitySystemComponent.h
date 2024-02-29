// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "PGFlowAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = ("Flow CAS"), meta = (BlueprintSpawnableComponent))
class POKEMONGASSAMPLE_API UPGFlowAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	FGameplayTag GetNextTag(const FGameplayTagContainer& CurrentContainer);

	UFUNCTION(BlueprintCallable, Category = "Flow CAS")
	void CancelAbilityWithTag(FGameplayTagContainer Tags);
	UFUNCTION(BlueprintCallable, Category = "Flow CAS")
	void EndAbilityWithTag(FGameplayTagContainer Tags);

	UFUNCTION(BlueprintCallable, Category = "Flow CAS")
	virtual void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor) override;
	
	UFUNCTION(BlueprintCallable, Category = "Flow GAS")
	virtual void OnTagUpdated(const FGameplayTag& Tag, bool TagExists) override;

protected:
	UFUNCTION()
	void EndAbilitySpec(FGameplayAbilitySpec& Spec);


protected:
	UPROPERTY(EditDefaultsOnly, Category=GAS)
	TMap<FGameplayTag, FGameplayTag> GameplayFlowTagMap;

	
};
