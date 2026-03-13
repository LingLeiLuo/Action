// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/HeroCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "ActionGameplayTags.h"
#include "Items/Weapons/ActionHeroWeapon.h"

AActionHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<AActionHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

AActionHeroWeapon* UHeroCombatComponent::GetHeroCurrentEquippedWeapon() const
{
	return Cast<AActionHeroWeapon>(GetCharacterCurrentEquippedWeapon());
}

float UHeroCombatComponent::GetHeroCurrentEquippedWeaponDamageAtLevel(float InLevel) const
{
	return GetHeroCurrentEquippedWeapon()->HeroWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel);
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

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), ActionGameplayTags::Player_Event_HitPause,
	                                                         FGameplayEventData());
}

void UHeroCombatComponent::OnPulledFromTargetActor(AActor* InInteractedActor)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), ActionGameplayTags::Player_Event_HitPause,
	                                                         FGameplayEventData());
}
