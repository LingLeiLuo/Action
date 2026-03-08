// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/ActionHeroWeapon.h"

void AActionHeroWeapon::AssignGrantedAbilitySpecHandles(TArray<FGameplayAbilitySpecHandle> InGrantedAbilitySpecHandles)
{
	GrantedAbilitySpecHandles = InGrantedAbilitySpecHandles;
}

TArray<FGameplayAbilitySpecHandle> AActionHeroWeapon::GetGrantedAbilitySpecHandles() const
{
	return GrantedAbilitySpecHandles;
}
