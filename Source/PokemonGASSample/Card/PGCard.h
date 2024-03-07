// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tag/PGGameplayTag.h"
#include "AbilitySystemInterface.h"
#include "PGCard.generated.h"

UCLASS()
class POKEMONGASSAMPLE_API APGCard : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APGCard();
	UFUNCTION(BlueprintCallable)
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:
	UFUNCTION(BlueprintCallable)
	class APGPlayerState* GetCardOwner() const;
	void SetCardOwner(class APGPlayerState* InOwner);

protected:
	UPROPERTY()
	TObjectPtr<class APGPlayerState> CardOwner;

	UPROPERTY(EditDefaultsOnly, Category = Card)
	TObjectPtr<UChildActorComponent> ImplementChildActor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Card)
	FName CardName;

	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UPGCardASC> ASC;

	UPROPERTY(EditDefaultsOnly, Category = GAS)
	TArray<TSubclassOf<class UGameplayAbility>> StartAbilities;
	UPROPERTY(EditDefaultsOnly, Category = GAS)
	TArray<TSubclassOf<class UGameplayEffect>> StartInfiniteEffects;
};
