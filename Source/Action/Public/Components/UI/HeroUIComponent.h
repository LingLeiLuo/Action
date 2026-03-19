// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/UI/PawnUIComponent.h"
#include "HeroUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEuqippedWeaponChangedDelegate, TSoftObjectPtr<UTexture2D>, SoftWeaponTexture);

/**
 * 
 */
UCLASS()
class ACTION_API UHeroUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnPercentChangedDelegate OnCurrentEnergyChanged;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnEuqippedWeaponChangedDelegate OnEquippedWeaponChanged;
};
