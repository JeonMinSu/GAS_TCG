// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PGMonster.generated.h"

UCLASS()
class POKEMONGASSAMPLE_API APGMonster : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APGMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY()
	TObjectPtr<class UAbilitySystemComponent> ASC;
	UPROPERTY(EditDefaultsOnly, Category = GAS)
	TObjectPtr<class UPGMonsterAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly, Category = GAS)
	TArray<TSubclassOf<class UGameplayAbility>> StartAbilities;
	UPROPERTY(EditDefaultsOnly, Category = GAS)
	TArray<TSubclassOf<class UGameplayEffect>> StartInfiniteEffects;
};
