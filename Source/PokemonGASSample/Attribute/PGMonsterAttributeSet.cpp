// Fill out your copyright notice in the Description page of Project Settings.


#include "Attribute/PGMonsterAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "PokemonGASSample.h"

UPGMonsterAttributeSet::UPGMonsterAttributeSet()
{
}

void UPGMonsterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{

}

void UPGMonsterAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	UE_LOG(LogPGGAS, Log, TEXT("%s Attribute Changed in Monster Attribute Set"), *Attribute.GetName());
}

void UPGMonsterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	float MinimumHealth = 0.0f;

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), MinimumHealth, GetMaxHealth()));
	}
	else if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth() - GetDamage(), MinimumHealth, GetMaxHealth()));
		SetDamage(0.0f);

		if (GetHealth() == MinimumHealth)
		{
			OnDefeat.ExecuteIfBound();
		}
	}
}
