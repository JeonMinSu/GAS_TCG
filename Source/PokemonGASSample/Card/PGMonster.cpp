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

FString StringConverter(FGameplayTag Tag)
{
	if (Tag.MatchesTagExact(PGTAG_CARD_MONSTER_ENERGY_DARK))
	{
		return FString(TEXT("악"));
	}
	else if (Tag.MatchesTagExact(PGTAG_CARD_MONSTER_ENERGY_ELECTRIC))
	{
		return FString(TEXT("전기"));
	}
	else if (Tag.MatchesTagExact(PGTAG_CARD_MONSTER_ENERGY_FIGHT))
	{
		return FString(TEXT("격투"));
	}
	else if (Tag.MatchesTagExact(PGTAG_CARD_MONSTER_ENERGY_FIRE))
	{
		return FString(TEXT("불"));
	}
	else if (Tag.MatchesTagExact(PGTAG_CARD_MONSTER_ENERGY_GRASS))
	{
		return FString(TEXT("풀"));
	}
	else if (Tag.MatchesTagExact(PGTAG_CARD_MONSTER_ENERGY_WATER))
	{
		return FString(TEXT("물"));
	}
	return FString(TEXT(""));
}

FString APGMonster::GetAttack1NameWithEnergy()
{
	int32 Count = 0;
	FString EnergyInfoString;
	for (const auto& Require : Attack1Require)
	{
		if (Require.Key.MatchesTagExact(PGTAG_CARD_MONSTER_ENERGY))
		{
			EnergyInfoString.Append(FString::Printf(TEXT(" 일반%d"), Require.Value - Count));
		}
		else
		{
			Count += Require.Value;
			EnergyInfoString.Append(FString::Printf(TEXT(" %s%d"), *StringConverter(Require.Key), Require.Value));
		}
	}

	return Attack1Name + EnergyInfoString;
}

FString APGMonster::GetAttack2NameWithEnergy()
{
	int32 Count = 0;
	FString EnergyInfoString;
	for (const auto& Require : Attack2Require)
	{
		if (Require.Key.MatchesTagExact(PGTAG_CARD_MONSTER_ENERGY))
		{
			EnergyInfoString.Append(FString::Printf(TEXT(" 일반%d"), Require.Value - Count));
		}
		else
		{
			Count += Require.Value;
			EnergyInfoString.Append(FString::Printf(TEXT(" %s%d"), *StringConverter(Require.Key), Require.Value));
		}
	}

	return Attack2Name + EnergyInfoString;
}

FString APGMonster::GetCurrentEnergyText()
{
	FGameplayTagContainer TagContainer;
	ASC->GetOwnedGameplayTags(TagContainer);
	TArray<FGameplayTag> OutTags;
	TagContainer.GetGameplayTagArray(OutTags);

	FString EnergyInfoString;
	for (FGameplayTag& Tag : OutTags)
	{
		if (Tag.MatchesTag(PGTAG_CARD_MONSTER_ENERGY))
		{
			EnergyInfoString.Append(FString::Printf(TEXT("%s%d "), *StringConverter(Tag), ASC->GetTagCount(Tag)));
		}
	}
	return EnergyInfoString;
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

