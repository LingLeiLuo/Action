// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/ActionBaseAnimInstance.h"
#include "ActionCharacterAnimInstance.generated.h"

class UCharacterMovementComponent;
class AActionBaseCharacter;
/**
 * 
 */
UCLASS()
class ACTION_API UActionCharacterAnimInstance : public UActionBaseAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY()
	AActionBaseCharacter* OwingCharacter;

	UPROPERTY()
	UCharacterMovementComponent* OwingCharacterMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float GroundSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bHasAcceleration;
};
