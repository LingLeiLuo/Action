// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/ActionBaseAnimInstance.h"

#include "ActionFunctionLibrary.h"
#include "GameplayTagContainer.h"

bool UActionBaseAnimInstance::DoesOwnerHaveTag(FGameplayTag InTag) const
{
	if (APawn* OwningPawn = TryGetPawnOwner())
	{
		return UActionFunctionLibrary::NativeDoesActorHaveTag(OwningPawn, InTag);
	}

	return false;
}
