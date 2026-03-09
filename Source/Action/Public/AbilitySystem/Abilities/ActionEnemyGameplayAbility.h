// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/ActionGameplayAbility.h"
#include "ActionEnemyGameplayAbility.generated.h"

class UEnemyCombatComponent;
class AActionEnemyCharacter;

/**
 * 
 */
UCLASS()
class ACTION_API UActionEnemyGameplayAbility : public UActionGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Action|Ability")
	AActionEnemyCharacter* GetEnemyCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Action|Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

private:
	TWeakObjectPtr<AActionEnemyCharacter> CachedActionEnemyCharacter;
};
