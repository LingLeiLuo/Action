// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ActionBaseCharacter.h"
#include "AbilitySystem/ActionAbilitySystemComponent.h"
#include "AbilitySystem/ActionAttributeSet.h"

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

	ActionAbilitySystemComponent = CreateDefaultSubobject<UActionAbilitySystemComponent>(
		TEXT("ActionAbilitySystemComponent"));

	ActionAttributeSet = CreateDefaultSubobject<UActionAttributeSet>(TEXT("ActionAttributeSet"));
}

/**
 * @brief 获取角色的能力系统组件
 * 
 * 重写 AActor 的 GetAbilitySystemComponent 方法，返回角色持有的能力系统组件。
 * 
 * @return 返回角色的能力系统组件指针
 */
UAbilitySystemComponent* AActionBaseCharacter::GetAbilitySystemComponent() const
{
	return GetActionAbilitySystemComponent();
}

/**
 * @brief 当角色被控制器控制时调用
 * 
 * 此函数在角色被指定控制器控制时触发，用于初始化角色的能力系统组件。
 * 它会调用父类的实现，然后初始化能力系统组件的Actor信息。
 * 
 * @param NewController 控制此角色的控制器实例
 */
void AActionBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (ActionAbilitySystemComponent)
	{
		ActionAbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}
