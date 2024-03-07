// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PGDeckData.generated.h"

/**
 * 
 */
UCLASS()
class POKEMONGASSAMPLE_API UPGDeckData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPGDeckData();

	UPROPERTY(EditAnywhere, Category = Card)
	TMap<TSubclassOf<class APGCard>, int32> DeckMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Card)
	FString DeckName;
};
