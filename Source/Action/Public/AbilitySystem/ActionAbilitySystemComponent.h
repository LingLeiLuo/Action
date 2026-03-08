// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ActionDefines/ActionStructDefines.h"
#include "ActionAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class ACTION_API UActionAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);
	void OnAbilityInputReleased(const FGameplayTag& InInputTag);

	UFUNCTION(BlueprintCallable, Category = "Action|Ability", meta = (ApplyLevel = "1"))
	void GrantHeroWeaponAbilities(const TArray<FActionHeroAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel,
	                              TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles);

	/**
	 * @brief 移除已授予的英雄武器能力
	 * 
	 * 从能力系统中移除指定英雄武器的能力规范句柄对应的能力
	 * 
	 * @param InGrantedAbilitySpecHandlesToRemove 需要移除的能力规范句柄数组（引用传递）
	 *
	 **/
	UFUNCTION(BlueprintCallable, Category = "Action|Ability")
	void RemovedGrantedHeroWeaponAbilities(
		UPARAM(ref)
		TArray<FGameplayAbilitySpecHandle>& InGrantedAbilitySpecHandlesToRemove);
};
