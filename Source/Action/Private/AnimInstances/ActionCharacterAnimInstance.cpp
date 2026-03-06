// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/ActionCharacterAnimInstance.h"

#include "Characters/ActionBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


void UActionCharacterAnimInstance::NativeInitializeAnimation()
{
	OwingCharacter = Cast<AActionBaseCharacter>(TryGetPawnOwner());

	if (OwingCharacter)
	{
		OwingCharacterMovementComponent = OwingCharacter->GetCharacterMovement();
	}
}

void UActionCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwingCharacter || !OwingCharacterMovementComponent)
	{
		return;
	}

	GroundSpeed = OwingCharacter->GetVelocity().Size2D();

	bHasAcceleration = OwingCharacterMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
}
