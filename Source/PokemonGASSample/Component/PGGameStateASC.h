// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Interface/AbilitySystem/PGFlowSystemInterface.h"
#include "PGGameStateASC.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = ("Flow GAS"), meta = (BlueprintSpawnableComponent))
class POKEMONGASSAMPLE_API UPGGameStateASC : public UAbilitySystemComponent, public IPGFlowSystemInterface
{
	GENERATED_BODY()
	
public:
	UPGGameStateASC();
	
// Interface
public:
	UFUNCTION()
	virtual FGameplayTag GetNextTag(const FGameplayTagContainer& CurrentContainer) override;
	UFUNCTION()
	virtual bool ActivateNextFlow(FGameplayTag ActivationTag) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "GAS")
	TMap<FGameplayTag, FGameplayTag> GameplayFlowTagMap;

public:
	UFUNCTION(BlueprintCallable, Category = "Flow GAS")
	void CancelAbilityWithTag(FGameplayTagContainer Tags);
	UFUNCTION(BlueprintCallable, Category = "Flow GAS")
	void EndAbilityWithTag(FGameplayTagContainer Tags);

	UFUNCTION(BlueprintCallable, Category = "Flow GAS")
	virtual void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor) override;
	
	UFUNCTION(BlueprintCallable, Category = "Flow GAS")
	virtual void OnTagUpdated(const FGameplayTag& Tag, bool TagExists) override;

protected:
	UFUNCTION()
	void EndAbilitySpec(FGameplayAbilitySpec& Spec);
};
