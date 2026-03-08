// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/HeroCombatComponent.h"

#include "Items/Weapons/ActionHeroWeapon.h"

AActionHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<AActionHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}
