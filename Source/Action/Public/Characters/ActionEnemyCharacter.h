// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ActionBaseCharacter.h"
#include "ActionEnemyCharacter.generated.h"

class UEnemyCombatComponent;
/**
 * 
 */
UCLASS()
class ACTION_API AActionEnemyCharacter : public AActionBaseCharacter
{
	GENERATED_BODY()

public:
	AActionEnemyCharacter();

	// IPawnCombatInterface 接口 Begin
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	// IPawnCombatInterface 接口 End

protected:
	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UEnemyCombatComponent* EnemyCombatComponent;

private:
	void InitEnemyStartUpData();

public:
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }
};
