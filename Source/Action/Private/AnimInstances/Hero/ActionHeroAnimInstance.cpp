// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Hero/ActionHeroAnimInstance.h"

#include "Characters/ActionHeroCharacter.h"

void UActionHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningCharacter)
	{
		OwingHeroCharacter = Cast<AActionHeroCharacter>(OwningCharacter);
	}
}

void UActionHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (bHasAcceleration)
	{
		IdleElapsedTime = 0.f;
		bShouldEnterRelaxState = false;
	}
	else
	{
		IdleElapsedTime += DeltaSeconds;
		bShouldEnterRelaxState = IdleElapsedTime > EnterRelaxStateThreshold;
	}
}
