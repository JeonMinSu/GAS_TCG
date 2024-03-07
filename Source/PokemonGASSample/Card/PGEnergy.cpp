// Fill out your copyright notice in the Description page of Project Settings.


#include "PGEnergy.h"
#include "AbilitySystemComponent.h"


// Sets default values
APGEnergy::APGEnergy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
}

// Called when the game starts or when spawned
void APGEnergy::BeginPlay()
{
	Super::BeginPlay();
	
}

void APGEnergy::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ASC->InitAbilityActorInfo(this, this);

	for (const auto& StartAbility : StartAbilities)
	{
		FGameplayAbilitySpec Spec(StartAbility);
		ASC->GiveAbility(Spec);
	}

	FGameplayEffectContextHandle EffectContextHandle = ASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	for (const auto& StartEffect : StartInfiniteEffects)
	{
		FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(StartEffect, 1, EffectContextHandle);

		if (EffectSpecHandle.IsValid())
		{
			ASC->BP_ApplyGameplayEffectSpecToSelf(EffectSpecHandle);
		}
	}
}

// Called every frame
void APGEnergy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

