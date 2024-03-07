// Fill out your copyright notice in the Description page of Project Settings.

#include "PGCardASC.h"
#include "Tag/PGGameplayTag.h"

UPGCardASC::UPGCardASC()
{
}

void UPGCardASC::OnTagUpdated(const FGameplayTag& Tag, bool TagExists)
{
	if (Tag.MatchesTag(PGTAG_CARD_STATUS) && TagExists)
	{

	}
}
