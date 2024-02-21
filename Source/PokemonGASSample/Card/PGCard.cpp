// Fill out your copyright notice in the Description page of Project Settings.


#include "PGCard.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"

// Sets default values
APGCard::APGCard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
}

UAbilitySystemComponent* APGCard::GetAbilitySystemComponent() const
{
	return ASC;
}

// Called when the game starts or when spawned
void APGCard::BeginPlay()
{
	Super::BeginPlay();
	
}

void APGCard::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ASC->InitAbilityActorInfo(this, this);

	for (const auto& StartAbility : StarrtAbilities)
	{
		FGameplayAbilitySpec Spec(StartAbility);
		ASC->GiveAbility(Spec);
	}

}

// Called every frame
void APGCard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

