// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/ActionGameplayAbility.h"
#include "Components/Combat/HeroCombatComponent.h"
#include "ActionHeroGameplayAbility.generated.h"

class AActionHeroController;
class AActionHeroCharacter;
/**
 * 
 */
UCLASS()
class ACTION_API UActionHeroGameplayAbility : public UActionGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="Action|Ability")
	AActionHeroCharacter* GetHeroCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category="Action|Ability")
	AActionHeroController* GetHeroControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category="Action|Ability")
	UHeroCombatComponent* GetHeroCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category="Action|Ability")
	FGameplayEffectSpecHandle MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass,
	                                                         float InWeaponBaseDamage,
	                                                         FGameplayTag InCurrentComboCount);

private:
	TWeakObjectPtr<AActionHeroCharacter> CachedActionHeroCharacter;
	TWeakObjectPtr<AActionHeroController> CachedActionHeroController;
};
