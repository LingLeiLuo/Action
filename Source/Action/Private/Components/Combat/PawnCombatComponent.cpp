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

	InWeaponToRegister->Dlgt_OnWeaponHitTarget.BindUObject(this, &ThisClass::OnHitTargetActor);
	InWeaponToRegister->Dlgt_OnWeaponPulledFromTarget.BindUObject(this, &ThisClass::OnPulledFromTargetActor);

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

		if (bEnable)
		{
			NeedToggleWeapon->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		}
		else
		{
			NeedToggleWeapon->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			// 当攻击结束时，缓存的碰撞接触的Actor数组清空
			OverlappedActors.Empty();
		}
	}
}

void UPawnCombatComponent::OnHitTargetActor(AActor* InHitActor)
{
}

void UPawnCombatComponent::OnPulledFromTargetActor(AActor* InInteractedActor)
{
}
