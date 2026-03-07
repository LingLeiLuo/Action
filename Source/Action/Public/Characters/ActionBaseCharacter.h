// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "ActionBaseCharacter.generated.h"

class UActionAttributeSet;
class UActionAbilitySystemComponent;

UCLASS()
class ACTION_API AActionBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AActionBaseCharacter();

	// IAbilitySystemInterface 接口 Begin
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// IAbilitySystemInterface 接口 End

protected:
	// APawn 接口 Begin
	virtual void PossessedBy(AController* NewController) override;
	// APawn 接口 End


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AbilitySystem")
	UActionAbilitySystemComponent* ActionAbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AbilitySystem")
	UActionAttributeSet* ActionAttributeSet;

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
