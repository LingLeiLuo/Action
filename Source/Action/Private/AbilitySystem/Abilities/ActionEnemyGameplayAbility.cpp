// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ActionEnemyGameplayAbility.h"

#include "ActionGameplayTags.h"
#include "AbilitySystem/ActionAbilitySystemComponent.h"
#include "Characters/ActionEnemyCharacter.h"

AActionEnemyCharacter* UActionEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (!CachedActionEnemyCharacter.IsValid())
	{
		CachedActionEnemyCharacter = Cast<AActionEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedActionEnemyCharacter.IsValid() ? CachedActionEnemyCharacter.Get() : nullptr;
}

UEnemyCombatComponent* UActionEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}

FGameplayEffectSpecHandle UActionEnemyGameplayAbility::MakeEnemyDamageEffectHandle(
	TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat)
{
	check(EffectClass);
	
	FGameplayEffectContextHandle EffectContextHandle = GetActionAbilitySystemComponentFromActorInfo()->
		MakeEffectContext();
	EffectContextHandle.SetAbility(this);
	EffectContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	EffectContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle EffectSpecHandle = GetActionAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
		EffectClass, GetAbilityLevel(),
		EffectContextHandle);

	EffectSpecHandle.Data->SetSetByCallerMagnitude(
		ActionGameplayTags::Shared_SetByCaller_BaseDamage,
		InDamageScalableFloat.GetValueAtLevel(GetAbilityLevel()));

	return EffectSpecHandle;
}


