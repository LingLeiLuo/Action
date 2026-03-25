// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ActionAbilitySystemComponent.h"

#include "ActionDebugHelper.h"
#include "AbilitySystem/Abilities/ActionHeroGameplayAbility.h"

/**
 * @brief 当输入标签被按下时调用，尝试激活匹配的游戏能力
 * 
 * 遍历所有可激活的能力，查找具有指定输入标签的能力并尝试激活。
 * 输入标签用于将按键输入与特定能力关联。
 * 
 * @param InInputTag 输入标签，标识要激活的能力对应的输入动作
 */
void UActionAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid())
	{
		return;
	}

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag))
		{
			// const FString log = FString::Printf(TEXT("InInputTag %s"), *InInputTag.ToString());
			// Debug::Print(log);
			continue;
		}

		TryActivateAbility(AbilitySpec.Handle);
	}
}

void UActionAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
}

void UActionAbilitySystemComponent::GrantHeroWeaponAbilities(
	const TArray<FActionHeroAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel,
	TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles)
{
	if (InDefaultWeaponAbilities.IsEmpty())
	{
		return;
	}

	for (const FActionHeroAbilitySet& AbilitySet : InDefaultWeaponAbilities)
	{
		if (!AbilitySet.IsValid())
		{
			continue;
		}

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

		OutGrantedAbilitySpecHandles.AddUnique(GiveAbility(AbilitySpec));
	}
}

void UActionAbilitySystemComponent::RemovedGrantedHeroWeaponAbilities(
	TArray<FGameplayAbilitySpecHandle>& InGrantedAbilitySpecHandlesToRemove)
{
	if (InGrantedAbilitySpecHandlesToRemove.IsEmpty())
	{
		return;
	}

	for (const FGameplayAbilitySpecHandle& AbilitySpecHandle : InGrantedAbilitySpecHandlesToRemove)
	{
		if (AbilitySpecHandle.IsValid())
		{
			ClearAbility(AbilitySpecHandle);
		}
	}

	InGrantedAbilitySpecHandlesToRemove.Empty();
}

bool UActionAbilitySystemComponent::TryActivateAbilityByTag(FGameplayTag InAbilityTag)
{
	check(InAbilityTag.IsValid());
	TArray<FGameplayAbilitySpec*> FoundAbilitySpecs;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(InAbilityTag.GetSingleTagContainer(), FoundAbilitySpecs);

	if (!FoundAbilitySpecs.IsEmpty())
	{
		const int32 RandomAbilityIndex = FMath::RandRange(0, FoundAbilitySpecs.Num() - 1);
		FGameplayAbilitySpec* AbilitySpecToActivate = FoundAbilitySpecs[RandomAbilityIndex];

		check(AbilitySpecToActivate);
		if (!AbilitySpecToActivate->IsActive())
		{
			return TryActivateAbility(AbilitySpecToActivate->Handle);
		}
	}

	return false;
}
