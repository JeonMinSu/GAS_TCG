// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "AbilitySystemInterface.h"
#include "PGGameState.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGenericPlayerEventDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDeckSeletedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerGameStartDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerEndTurnDelegate, int32, PlayerIndex);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerDeckSeletedDelegate, class APlayerState*, PlayerState);
UCLASS()
class POKEMONGASSAMPLE_API APGGameState : public AGameState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APGGameState();

	UFUNCTION(BlueprintCallable, Category = "GAS")
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void PreInitializeComponents() override;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GAS)
	TObjectPtr<class UPGGameStateASC> ASC;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GAS)
	TArray<TSubclassOf<class UGameplayAbility>> StartAbilities;
	
};
