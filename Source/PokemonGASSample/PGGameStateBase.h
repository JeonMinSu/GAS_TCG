// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AbilitySystemInterface.h"
#include "PGGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class POKEMONGASSAMPLE_API APGGameStateBase : public AGameStateBase, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	APGGameStateBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void PostInitializeComponents() override;

protected:
	UPROPERTY()
	TObjectPtr<class UAbilitySystemComponent> ASC;
	
};
