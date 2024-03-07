// Fill out your copyright notice in the Description page of Project Settings.


#include "Card/PGMonster.h"
#include "AbilitySystemComponent.h"
#include "Attribute/PGMonsterAttributeSet.h"
#include "Tag/PGGameplayTag.h"
#include "PGCard.h"
#include "PokemonGASSample.h"

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

	if (AttribuetDataTable)
	{
		AttributeSet->InitFromMetaDataTable(AttribuetDataTable);
	}

	if (AttributeInitializeEffect)
	{
		FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(AttributeInitializeEffect, 1, EffectContextHandle);

		if (EffectSpecHandle.IsValid())
		{
			ASC->BP_ApplyGameplayEffectSpecToSelf(EffectSpecHandle);
		}
	}

	AttributeSet->OnDefeat.BindUObject(this, &APGMonster::OnDefeatCallback);
}

// Called every frame
void APGMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool APGMonster::GetAttack1Activatable()
{
	bool Attackable = true;
	for (const auto& GameplayTag : Attack1Require)
	{
		Attackable = Attackable && ASC->GetGameplayTagCount(GameplayTag.Key) >= GameplayTag.Value;
	}
	return Attackable;
}

bool APGMonster::GetAttack2Activatable()
{
	bool Attackable = true;
	for (const auto& GameplayTag : Attack2Require)
	{
		int32 TagCount = ASC->GetGameplayTagCount(GameplayTag.Key);
		PGGAS_LOG(LogPGGASTAG, Log, TEXT("%s tag number is now %d"), *GameplayTag.Key.ToString(), TagCount);
		Attackable = Attackable && ASC->GetGameplayTagCount(GameplayTag.Key) >= GameplayTag.Value;
	}
	return Attackable;
}

bool APGMonster::TryAttack1()
{
	bool Activated = false;
	if (GetAttack1Activatable())
	{
		FGameplayTagContainer TagContainer(PGTAG_CARD_MONSTER_ACTION_ATTACK1);
		Activated = ASC->TryActivateAbilitiesByTag(TagContainer);
	}

	return Activated;
}

bool APGMonster::TryAttack2()
{
	bool Activated = false;
	if (GetAttack2Activatable())
	{
		FGameplayTagContainer TagContainer(PGTAG_CARD_MONSTER_ACTION_ATTACK2);
		Activated = ASC->TryActivateAbilitiesByTag(TagContainer);
	}

	return Activated;
}

void APGMonster::AttachEnergy(APGCard* Card, FGameplayTag LooseAddTag)
{
	UAbilitySystemComponent* CardASC = Card->GetAbilitySystemComponent();

	if (CardASC->HasMatchingGameplayTag(PGTAG_CARD_TYPE_ENERGY))
	{
		AttachedEnergyCards.Add(Card);

		ASC->AddLooseGameplayTag(LooseAddTag);
	}
}

void APGMonster::OnDefeatCallback()
{
	UAbilitySystemComponent* CardASC = CastChecked<APGCard>(GetParentActor())->GetAbilitySystemComponent();
	FGameplayTagContainer TagContainer(PGTAG_CARD_ACTION_2TRASH);
	CardASC->TryActivateAbilitiesByTag(TagContainer);

	for (APGCard* Card : AttachedEnergyCards)
	{
		CardASC = Card->GetAbilitySystemComponent();
		CardASC->TryActivateAbilitiesByTag(TagContainer);
	}
}

