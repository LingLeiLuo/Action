// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GenericTeamAgentInterface.h"
#include "AbilitySystem/ActionAbilitySystemComponent.h"
#include "Characters/ActionBaseCharacter.h"

/**
 * @brief 从 Actor 获取 ActionAbilitySystemComponent 组件
 * 
 * @param InActor 目标 Actor，不能为空
 * @return UActionAbilitySystemComponent* 返回 Actor 上的 ActionAbilitySystemComponent 组件
 * @throws 如果 InActor 为空或转换失败，将触发断言
 */
UActionAbilitySystemComponent* UActionFunctionLibrary::NativeGetActionActionAbilitySystemComponentFromActor(
	AActor* InActor)
{
	check(InActor);

	return CastChecked<UActionAbilitySystemComponent>(
		UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

/**
 * @brief 如果 Actor 不存在指定的 Gameplay Tag，则为其添加该标签
 * 
 * 该函数会检查目标 Actor 是否已拥有指定的 Gameplay Tag，如果不存在则添加。
 * 该操作使用 Loose Game Tag 方式，不会影响 Tag 的数量计数。
 * 
 * @param InActor 目标 Actor 指针，不能为空
 * @param InGameplayTagToAdd 要添加的 Gameplay Tag，必须有效
 * 
 * @throws 如果 InActor 为空指针会触发断言失败
 * @throws 如果 InGameplayTagToAdd 无效会触发断言失败
 */
void UActionFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag InGameplayTagToAdd)
{
	check(InActor);
	check(InGameplayTagToAdd.IsValid());

	UActionAbilitySystemComponent* AbilitySystemComponent =
		NativeGetActionActionAbilitySystemComponentFromActor(InActor);
	if (!AbilitySystemComponent->HasMatchingGameplayTag(InGameplayTagToAdd))
	{
		AbilitySystemComponent->AddLooseGameplayTag(InGameplayTagToAdd);
	}
}

/**
 * @brief 如果 Actor 拥有指定的游戏标签，则从其移除该标签
 * 
 * 该函数会检查指定的 Actor 是否包含给定的游戏标签，如果存在则将其移除。
 * 此操作仅对松散标签（Loose Tag）生效。
 * 
 * @param InActor 目标 Actor，不能为空
 * @param InGameplayTagToRemove 要移除的游戏标签，必须有效
 * 
 * @throws 如果 InActor 为空指针，会触发断言错误
 * @throws 如果 InGameplayTagToRemove 无效，会触发断言错误
 */
void UActionFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag InGameplayTagToRemove)
{
	check(InActor);
	check(InGameplayTagToRemove.IsValid());

	UActionAbilitySystemComponent* AbilitySystemComponent =
		NativeGetActionActionAbilitySystemComponentFromActor(InActor);

	if (AbilitySystemComponent->HasMatchingGameplayTag(InGameplayTagToRemove))
	{
		AbilitySystemComponent->RemoveLooseGameplayTag(InGameplayTagToRemove);
	}
}

/**
 * @brief 检查指定 Actor 是否具有特定的 Gameplay Tag
 * 
 * @param InActor 要检查的 Actor
 * @param InGameplayTagToCheck 要查询的 Gameplay Tag
 * @return bool 如果 Actor 具有指定的 Gameplay Tag 则返回 true，否则返回 false
 */
bool UActionFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag InGameplayTagToCheck)
{
	UActionAbilitySystemComponent* AbilitySystemComponent =
		NativeGetActionActionAbilitySystemComponentFromActor(InActor);

	return AbilitySystemComponent->HasMatchingGameplayTag(InGameplayTagToCheck);
}

/**
 * @brief 检查指定Actor是否拥有特定的Gameplay标签
 * 
 * 这是一个蓝图可调用的函数，用于判断Actor是否包含给定的Gameplay标签，
 * 并将结果以确认类型的形式返回。
 * 
 * @param InActor 要检查的Actor指针
 * @param InGameplayTagToCheck 需要检查的Gameplay标签
 * @param OutConfirmType 输出参数，返回确认类型：Yes表示拥有该标签，No表示未拥有
 */
void UActionFunctionLibrary::K2_DoesActorHaveTag(AActor* InActor, FGameplayTag InGameplayTagToCheck,
                                                 EActionConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor, InGameplayTagToCheck)
		                 ? EActionConfirmType::Yes
		                 : EActionConfirmType::No;
}

/**
 * @brief 从 Actor 原生获取 Pawn 战斗组件
 * 
 * 该函数尝试从指定的 Actor 中获取战斗组件。Actor 必须实现 IPawnCombatInterface 接口。
 * 
 * @param InActor 要获取战斗组件的 Actor，不能为空
 * @return 如果 Actor 实现了 IPawnCombatInterface 接口，则返回其战斗组件指针；否则返回 nullptr
 * @throws 如果 InActor 为空，则触发断言失败
 */
UPawnCombatComponent* UActionFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	check(InActor);

	if (IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
	{
		return PawnCombatInterface->GetPawnCombatComponent();
	}

	return nullptr;
}

/**
 * @brief 从Actor获取Pawn战斗组件（蓝图可调用版本）
 * 
 * 该函数是NativeGetPawnCombatComponentFromActor的K2（蓝图）封装版本，
 * 用于从指定的Actor中获取UPawnCombatComponent组件，并通过输出参数返回验证结果。
 * 
 * @param InActor 要查询的Actor指针
 * @param OutValidType 输出参数，返回组件获取是否有效的验证结果
 * @return UPawnCombatComponent* 获取到的战斗组件指针，如果Actor不包含该组件则返回nullptr
 */
UPawnCombatComponent* UActionFunctionLibrary::K2_GetPawnCombatComponentFromActor(AActor* InActor,
	EActionValidType& OutValidType)
{
	UPawnCombatComponent* CombatComponent = NativeGetPawnCombatComponentFromActor(InActor);

	OutValidType = CombatComponent ? EActionValidType::Valid : EActionValidType::Invalid;

	return CombatComponent;
}

bool UActionFunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
	check(QueryPawn && TargetPawn);
	
	IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	IGenericTeamAgentInterface* TargetQueryTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	if (QueryTeamAgent && TargetQueryTeamAgent)
	{
		return QueryTeamAgent->GetGenericTeamId() != TargetQueryTeamAgent->GetGenericTeamId();
	}
	
	return false;
}
