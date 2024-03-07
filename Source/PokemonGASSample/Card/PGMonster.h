// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
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

	UFUNCTION(BlueprintCallable)
	bool GetAttack1Activatable();
	UFUNCTION(BlueprintCallable)
	bool GetAttack2Activatable();
	UFUNCTION(BlueprintCallable)
	bool TryAttack1();
	UFUNCTION(BlueprintCallable)
	bool TryAttack2();
	UFUNCTION(BlueprintCallable)
	void AttachEnergy(class APGCard* Card, FGameplayTag LooseAddTag);

	void OnDefeatCallback();

protected:
	UPROPERTY(BlueprintReadOnly, Category = GAS)
	TArray<TObjectPtr<class APGCard>> AttachedEnergyCards;

	UPROPERTY()
	TObjectPtr<class UAbilitySystemComponent> ASC;
	UPROPERTY(EditDefaultsOnly, Category = GAS)
	TObjectPtr<class UPGMonsterAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly, Category = GAS)
	TArray<TSubclassOf<class UGameplayAbility>> StartAbilities;
	UPROPERTY(EditDefaultsOnly, Category = GAS)
	TArray<TSubclassOf<class UGameplayEffect>> StartInfiniteEffects;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GAS)
	FString Attack1Name;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GAS)
	FString Attack2Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GAS)
	TSubclassOf<class UGameplayEffect> AttackEffect1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GAS)
	TSubclassOf<class UGameplayEffect> AttackEffect2;

	UPROPERTY(EditDefaultsOnly, Category = GAS)
	TMap<FGameplayTag, int32> Attack1Require;
	UPROPERTY(EditDefaultsOnly, Category = GAS)
	TMap<FGameplayTag, int32> Attack2Require;

	UPROPERTY(EditDefaultsOnly, Category = GAS)
	TObjectPtr<class UDataTable> AttribuetDataTable;
	UPROPERTY(EditDefaultsOnly, Category = GAS)
	TSubclassOf<UGameplayEffect> AttributeInitializeEffect;

	// sprite asset
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Card)
	TWeakObjectPtr<class UTexture2D> Sprite;
};
