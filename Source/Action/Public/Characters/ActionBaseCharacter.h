// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/PawnCombatInterface.h"
#include "Interfaces/PawnUIInterface.h"
#include "ActionBaseCharacter.generated.h"

class UDataAsset_StartUpDataBase;
class UActionAttributeSet;
class UActionAbilitySystemComponent;

UCLASS()
class ACTION_API AActionBaseCharacter : public ACharacter, public IAbilitySystemInterface, public IPawnCombatInterface, public IPawnUIInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AActionBaseCharacter();

	// IAbilitySystemInterface 接口 Begin
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// IAbilitySystemInterface 接口 End

	// IPawnCombatInterface 接口 Begin
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	// IPawnCombatInterface 接口 End

	virtual UPawnUIComponent* GetPawnUIComponent() const override;

protected:
	// APawn 接口 Begin
	virtual void PossessedBy(AController* NewController) override;
	// APawn 接口 End


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem")
	UActionAbilitySystemComponent* ActionAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem")
	UActionAttributeSet* ActionAttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="CharacterData")
	TSoftObjectPtr<UDataAsset_StartUpDataBase> CharacterStartUpData;

public:
	FORCEINLINE UActionAbilitySystemComponent* GetActionAbilitySystemComponent() const
	{
		return ActionAbilitySystemComponent;
	}

	FORCEINLINE UActionAttributeSet* GetUActionAttributeSet() const
	{
		return ActionAttributeSet;
	}
};
