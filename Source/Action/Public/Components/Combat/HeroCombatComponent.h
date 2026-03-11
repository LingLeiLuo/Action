// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "HeroCombatComponent.generated.h"

class AActionHeroWeapon;
/**
 * 
 */
UCLASS()
class ACTION_API UHeroCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Action|Combat")
	AActionHeroWeapon* GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const;

	virtual void OnHitTargetActor(AActor* InHitActor) override;
	virtual void OnPulledFromTargetActor(AActor* InInteractedActor) override;
};
