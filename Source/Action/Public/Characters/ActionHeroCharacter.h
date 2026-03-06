// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ActionBaseCharacter.h"
#include "ActionHeroCharacter.generated.h"

struct FInputActionValue;
class UDataAsset_InputConfig;
class USpringArmComponent;
class UCameraComponent;


UCLASS()
class ACTION_API AActionHeroCharacter : public AActionBaseCharacter
{
	GENERATED_BODY()

public:
	AActionHeroCharacter();

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;

#pragma region Components

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess="true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess="true"))
	UCameraComponent* FollowCamera;

#pragma endregion


#pragma region Inputs

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="CharacterData", meta=(AllowPrivateAccess="true"))
	UDataAsset_InputConfig* InputConfigDataAsset;

	void Input_Move(const FInputActionValue& InInputActionValue);
	void Input_Look(const FInputActionValue& InInputActionValue);
#pragma endregion
};
