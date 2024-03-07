// Fill out your copyright notice in the Description page of Project Settings.


#include "PGCard.h"
#include "Abilities/GameplayAbility.h"
#include "Component/PGCardASC.h"

// Sets default values
APGCard::APGCard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ImplementChildActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("ChildActor"));
	ASC = CreateDefaultSubobject<UPGCardASC>(TEXT("ASC"));
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
void APGCard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

