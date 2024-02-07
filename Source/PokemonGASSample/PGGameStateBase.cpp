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
	// 실제 조정하고 관리하는 실제 작업이 이뤄나고 있는 Actor
	// 비주얼로 처리해주는 Actor
	ASC->InitAbilityActorInfo(this, this);
}
