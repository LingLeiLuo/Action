// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"

#include "AbilitySystem/ActionAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/ActionGameplayAbility.h"


/**
 * @brief 将启动数据授予指定的能力系统组件
 * @param InActionASCToGive 目标能力系统组件指针，必须有效
 * @param ApplyLevel 应用能力的等级
 * @note 此函数会授予激活时触发的技能、重新激活的技能，并应用所有启动效果
 */
void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UActionAbilitySystemComponent* InActionASCToGive,
                                                              int32 ApplyLevel)
{
	check(InActionASCToGive);

	GrantAbilities(ActivateOnGivenAbilities, InActionASCToGive, ApplyLevel);
	GrantAbilities(ReActivateAbilities, InActionASCToGive, ApplyLevel);

	if (!StartUpEffects.IsEmpty())
	{
		for (const TSubclassOf<UGameplayEffect>& EffectClass : StartUpEffects)
		{
			if (!EffectClass)
			{
				continue;
			}

			UGameplayEffect* EffectCDO = EffectClass->GetDefaultObject<UGameplayEffect>();
			InActionASCToGive->ApplyGameplayEffectToSelf(EffectCDO, ApplyLevel, InActionASCToGive->MakeEffectContext());
		}
	}
}

/**
 * @brief 向指定的能力系统组件授予一组游戏能力
 * 
 * 遍历输入的能力类数组，为每个有效的能力创建规格并授予给目标能力系统组件。
 * 能力规格的源对象设置为能力系统组件的化身角色，等级设置为指定值。
 * 
 * @param InAbilitiesToGive 需要授予的游戏能力类数组
 * @param InActionASCToGive 接收能力的目标能力系统组件
 * @param ApplyLevel 应用于能力的等级
 */
void UDataAsset_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<UActionGameplayAbility>>& InAbilitiesToGive,
                                                UActionAbilitySystemComponent* InActionASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty())
	{
		return;
	}

	for (const TSubclassOf<UActionGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability)
		{
			continue;
		}

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InActionASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;

		InActionASCToGive->GiveAbility(AbilitySpec);
	}
}
