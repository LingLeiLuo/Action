// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/EnemyCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "ActionDebugHelper.h"
#include "ActionGameplayTags.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* InHitActor)
{
	if (OverlappedActors.Contains(InHitActor))
	{
		return;
	}

	OverlappedActors.AddUnique(InHitActor);

	bool bIsValidBlock = false;

	const bool bIsPlayerBlocking = false;
	const bool bIsMyAttackUnblockable = false;


	if (bIsPlayerBlocking && !bIsMyAttackUnblockable)
	{
		
	}

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = InHitActor;

	if (bIsValidBlock)
	{
		
	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			GetOwningPawn(),
			ActionGameplayTags::Shared_Event_MeleeHit,
			EventData
		);
	}
}
