// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "PGMonsterAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
UCLASS()
class POKEMONGASSAMPLE_API UPGMonsterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UPGMonsterAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	ATTRIBUTE_ACCESSORS(UPGMonsterAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UPGMonsterAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UPGMonsterAttributeSet, Damage);
	ATTRIBUTE_ACCESSORS(UPGMonsterAttributeSet, Attack1Power);
	ATTRIBUTE_ACCESSORS(UPGMonsterAttributeSet, Attack2Power);

protected:
	UPROPERTY(BlueprintReadOnly, Category = Monster, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Health;
	UPROPERTY(BlueprintReadOnly, Category = Monster, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;
	UPROPERTY(BlueprintReadOnly, Category = Monster, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Damage;

	UPROPERTY(BlueprintReadOnly, Category = Monster, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Attack1Power;
	UPROPERTY(BlueprintReadOnly, Category = Monster, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Attack2Power;
};
