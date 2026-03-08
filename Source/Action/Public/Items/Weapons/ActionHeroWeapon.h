// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/ActionWeaponBase.h"
#include "ActionDefines/ActionStructDefines.h"
#include "GameplayAbilitySpecHandle.h"

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

	UFUNCTION(BlueprintCallable)
	void AssignGrantedAbilitySpecHandles(TArray<FGameplayAbilitySpecHandle> InGrantedAbilitySpecHandles);

	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const;

private:
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;
};
