// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

/**
 * @file ActionGameplayTags
 * @brief 动作游戏的游戏标签命名空间
 * 
 * 该命名空间定义了游戏中使用的各种游戏标签，主要用于输入系统、状态管理等场景。
 * 游戏标签提供了一种类型安全的方式来标识和匹配游戏中的各种状态和事件。
 */
namespace ActionGameplayTags
{
	ACTION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move)
	ACTION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look)
	ACTION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_EquipAxe)
	ACTION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UnEquipAxe)

	ACTION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Axe);

	ACTION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Axe);
	ACTION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_UnEquip_Axe);
}
