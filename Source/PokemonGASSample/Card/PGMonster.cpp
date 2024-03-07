// Fill out your copyright notice in the Description page of Project Settings.


#include "Card/PGMonster.h"
#include "AbilitySystemComponent.h"
#include "Attribute/PGMonsterAttributeSet.h"

// Sets default values
APGMonster::APGMonster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	AttributeSet = CreateDefaultSubobject<UPGMonsterAttributeSet>(TEXT("AttributeSet"));
}

// Called when the game starts or when spawned
void APGMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

void APGMonster::PostInitializeComponents()
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
void APGMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

