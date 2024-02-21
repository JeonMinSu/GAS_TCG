// Fill out your copyright notice in the Description page of Project Settings.


#include "PGPawn.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include <PokemonGASSample/Player/PGPlayerState.h>

// Sets default values
APGPawn::APGPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ASC = nullptr;
}

UAbilitySystemComponent* APGPawn::GetAbilitySystemComponent() const
{
	return ASC;
}

// Called when the game starts or when spawned
void APGPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APGPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APGPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APGPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	APGPlayerState* PGPS = GetPlayerState<APGPlayerState>();
	if (PGPS)
	{
		ASC = PGPS->GetAbilitySystemComponent();
		ASC->InitAbilityActorInfo(PGPS, this);
		for (const auto& StartAbility : StartAbilities)
		{
			FGameplayAbilitySpec Spec(StartAbility);
			ASC->GiveAbility(Spec);
		}
	}

}

