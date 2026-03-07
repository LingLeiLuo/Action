// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"

#include "AbilitySystem/ActionAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/ActionGameplayAbility.h"

/**
 * @brief 将启动数据中的能力授予指定的能力系统组件
 * 
 * 此函数会遍历并授予两类能力列表：
 * - ActivateOnGivenAbilities：首次授予时激活的能力
 * - ReActivateAbilities：需要重新激活的能力
 * 
 * @param InActionASCToGive 目标能力系统组件指针，必须有效
 * @param ApplyLevel 应用能力的等级，用于确定能力的强度
 * 
 * @throws 如果 InActionASCToGive 为空指针，将触发断言失败
 */
void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UActionAbilitySystemComponent* InActionASCToGive,
                                                              int32 ApplyLevel)
{
	check(InActionASCToGive);

	GrantAbilities(ActivateOnGivenAbilities, InActionASCToGive, ApplyLevel);
	GrantAbilities(ReActivateAbilities, InActionASCToGive, ApplyLevel);
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
