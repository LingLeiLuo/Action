// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/PawnCombatComponent.h"

#include "ActionDebugHelper.h"
#include "Components/BoxComponent.h"
#include "Items/Weapons/ActionWeaponBase.h"

void UPawnCombatComponent::RegisterSpawnWeapon(FGameplayTag InWeaponTagToRegister,
                                               AActionWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister),
	       TEXT("Weapon tag %s already exists in CharacterCarriedWeaponMap"), *InWeaponTagToRegister.ToString())
	check(InWeaponToRegister);

	CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);

	if (bRegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = InWeaponTagToRegister;
	}

	// const FString Weapon = FString::Printf(
	// 	TEXT("RegisterSpawnWeapon WeaponName: %s, WeaponTag: %s"), *InWeaponToRegister->GetName(),
	// 	*InWeaponTagToRegister.ToString());
	// Debug::Print(Weapon);
}

AActionWeaponBase* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	if (CharacterCarriedWeaponMap.Contains(InWeaponTag))
	{
		if (AActionWeaponBase* const* FoundWeapon = CharacterCarriedWeaponMap.Find(InWeaponTag))
		{
			return *FoundWeapon;
		}
	}

	return nullptr;
}

AActionWeaponBase* UPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid())
	{
		return nullptr;
	}

	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}

void UPawnCombatComponent::ToggleWeaponCollision(bool bEnable, EToggleDmgType ToggleDmgType)
{
	if (ToggleDmgType == EToggleDmgType::CurrentEquippedWeapon)
	{
		AActionWeaponBase* NeedToggleWeapon = GetCharacterCurrentEquippedWeapon();

		check(NeedToggleWeapon);

		NeedToggleWeapon->GetWeaponCollisionBox()->SetCollisionEnabled(bEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
	}
}
