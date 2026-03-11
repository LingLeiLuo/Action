// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/HeroCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "ActionDebugHelper.h"
#include "ActionGameplayTags.h"
#include "Items/Weapons/ActionHeroWeapon.h"

AActionHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<AActionHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

void UHeroCombatComponent::OnHitTargetActor(AActor* InHitActor)
{
	if (OverlappedActors.Contains(InHitActor))
	{
		return;
	}

	OverlappedActors.AddUnique(InHitActor);

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = InHitActor;

	// OverlappedActors
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), ActionGameplayTags::Shared_Event_MeleeHit,
	                                                         EventData);
}

void UHeroCombatComponent::OnPulledFromTargetActor(AActor* InInteractedActor)
{
}
