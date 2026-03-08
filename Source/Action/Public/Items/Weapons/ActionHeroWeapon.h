// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/ActionWeaponBase.h"
#include "ActionDefines/ActionStructDefines.h"
#include "ActionHeroWeapon.generated.h"

/**
 * 
 */
UCLASS()
class ACTION_API AActionHeroWeapon : public AActionWeaponBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
	FActionHeroWeaponData HeroWeaponData;
};
