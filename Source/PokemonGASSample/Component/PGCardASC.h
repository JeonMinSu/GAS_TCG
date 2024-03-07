// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "PGCardASC.generated.h"

/**
 * 
 */
UCLASS()
class POKEMONGASSAMPLE_API UPGCardASC : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	UPGCardASC();

	UFUNCTION(BlueprintCallable, Category = "GAS")
	virtual void OnTagUpdated(const FGameplayTag& Tag, bool TagExists) override;
};
