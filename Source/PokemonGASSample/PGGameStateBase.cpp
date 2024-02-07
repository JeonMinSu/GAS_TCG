// Fill out your copyright notice in the Description page of Project Settings.


#include "PGGameStateBase.h"
#include "AbilitySystemComponent.h"

APGGameStateBase::APGGameStateBase()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
}


UAbilitySystemComponent* APGGameStateBase::GetAbilitySystemComponent() const
{
	return ASC;
}

void APGGameStateBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	// ���� �����ϰ� �����ϴ� ���� �۾��� �̷ﳪ�� �ִ� Actor
	// ���־�� ó�����ִ� Actor
	ASC->InitAbilityActorInfo(this, this);
}
