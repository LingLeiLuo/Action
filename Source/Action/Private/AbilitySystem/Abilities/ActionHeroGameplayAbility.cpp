// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ActionHeroGameplayAbility.h"

#include "Characters/ActionHeroCharacter.h"
#include "Controllers/ActionHeroController.h"

AActionHeroCharacter* UActionHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
	if (!CachedActionHeroCharacter.IsValid())
	{
		CachedActionHeroCharacter = Cast<AActionHeroCharacter>(CurrentActorInfo->AvatarActor);
	}
	return CachedActionHeroCharacter.IsValid() ? CachedActionHeroCharacter.Get() : nullptr;
}

AActionHeroController* UActionHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
	if (!CachedActionHeroController.IsValid())
	{
		CachedActionHeroController = Cast<AActionHeroController>(CurrentActorInfo->PlayerController);
	}
	return CachedActionHeroController.IsValid() ? CachedActionHeroController.Get() : nullptr;
}

UHeroCombatComponent* UActionHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
	return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}

FGameplayEffectSpecHandle UActionHeroGameplayAbility::MakeHeroDamageEffectSpecHandle(
	TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentComboCount)
{
	check(EffectClass);

	FGameplayEffectContextHandle EffectContextHandle = GetActionAbilitySystemComponentFromActorInfo()->
		MakeEffectContext();
	EffectContextHandle.SetAbility(this);
	EffectContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	EffectContextHandle.AddInstigator(GetHeroCharacterFromActorInfo(), GetAvatarActorFromActorInfo());

	GetActionAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(EffectClass, GetAbilityLevel(), );
}
