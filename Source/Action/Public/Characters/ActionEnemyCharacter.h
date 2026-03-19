// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ActionBaseCharacter.h"
#include "Components/UI/EnemyUIComponent.h"
#include "ActionEnemyCharacter.generated.h"

class UWidgetComponent;
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

	virtual UPawnUIComponent* GetPawnUIComponent() const override;

	virtual UEnemyUIComponent* GetEnemyUIComponent() const override;

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UEnemyCombatComponent* EnemyCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UEnemyUIComponent* EnemyUIComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* EnemyHealthWidgetComponent;

private:
	void InitEnemyStartUpData();

public:
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }
};
