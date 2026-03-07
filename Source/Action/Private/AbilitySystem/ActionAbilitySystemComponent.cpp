// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ActionAbilitySystemComponent.h"

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
			continue;
		}

		TryActivateAbility(AbilitySpec.Handle);
	}
}

void UActionAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
}
