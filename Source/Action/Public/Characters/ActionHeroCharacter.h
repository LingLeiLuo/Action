// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ActionBaseCharacter.h"
#include "ActionHeroCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;


UCLASS()
class ACTION_API AActionHeroCharacter : public AActionBaseCharacter
{
	GENERATED_BODY()

public:
	AActionHeroCharacter();

protected:
	virtual void BeginPlay() override;

#pragma region Components

	UPROPERTY(VisibleAnywhere, Blueprintable, Category="Camera", meta=(AllowPrivateAccess="true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Blueprintable, Category="Camera", meta=(AllowPrivateAccess="true"))
	UCameraComponent* FollowCamera;

#pragma endregion
};
