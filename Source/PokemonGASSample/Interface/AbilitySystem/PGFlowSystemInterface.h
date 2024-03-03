// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "PGFlowSystemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPGFlowSystemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class POKEMONGASSAMPLE_API IPGFlowSystemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/*
	* Should return proper tag for next flow
	*/
	virtual FGameplayTag GetNextTag(const FGameplayTagContainer& CurrentContainer) = 0;
	virtual bool ActivateNextFlow(FGameplayTag ActivationTag) = 0;
};
