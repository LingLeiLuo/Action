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
	/**
	 * @brief 移动输入标签
	 * 
	 * 用于标识角色移动相关的输入动作，包括前后左右移动等基本移动操作。
	 */
	ACTION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);

	/**
	 * @brief 视角控制标签
	 * 
	 * 用于标识视角控制相关的输入动作，包括鼠标或手柄的视角旋转操作。
	 */
	ACTION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);
}
