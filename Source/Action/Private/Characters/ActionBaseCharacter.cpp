// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ActionBaseCharacter.h"

/**
 * @brief 构造函数
 * 
 * 初始化 AActionBaseCharacter 实例，设置默认属性值
 * - 禁用 Tick 功能以提升性能
 * - 禁用角色网格接收贴花效果
 */
AActionBaseCharacter::AActionBaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;
}
