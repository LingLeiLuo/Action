// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGameplayTags.h"

/**
 * @file ActionGameplayTags
 * @brief 定义输入相关的游戏标签
 * 
 * 该命名空间包含用于输入系统标识的游戏标签，用于映射输入动作到游戏逻辑
 */
namespace ActionGameplayTags
{
	/**
	 * @brief 移动输入标签
	 * @details 标识角色移动相关的输入动作
	 */
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "Input.Move");

	/**
	 * @brief 视角控制标签
	 * @details 标识角色视角旋转相关的输入动作
	 */
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "Input.Look");
}
