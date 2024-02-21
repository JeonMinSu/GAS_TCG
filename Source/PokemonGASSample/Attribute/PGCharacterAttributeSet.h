// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "PGCharacterAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class POKEMONGASSAMPLE_API UPGCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UPGCharacterAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	ATTRIBUTE_ACCESSORS(UPGCharacterAttributeSet, DeckCount);
	ATTRIBUTE_ACCESSORS(UPGCharacterAttributeSet, MaxDeckCount);
	ATTRIBUTE_ACCESSORS(UPGCharacterAttributeSet, HandCount);

protected:
	UPROPERTY(BlueprintReadOnly, Category = Deck, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData DeckCount;

	UPROPERTY(BlueprintReadOnly, Category = Deck, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxDeckCount;

	UPROPERTY(BlueprintReadOnly, Category = Hand, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData HandCount;

	UPROPERTY(BlueprintReadOnly, Category = Hand, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHandCount;

	UPROPERTY(BlueprintReadOnly, Category = Bench, Meta = (AllowPrivateAceess = true))
	FGameplayAttributeData BenchCardCount;

	UPROPERTY(BlueprintReadOnly, Category = Bench, Meta = (AllowPrivateAceess = true))
	FGameplayAttributeData MaxBenchCardCount;

};
