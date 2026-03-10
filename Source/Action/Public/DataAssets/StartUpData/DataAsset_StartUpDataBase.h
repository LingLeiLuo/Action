// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpDataBase.generated.h"

class UGameplayEffect;
class UActionAbilitySystemComponent;
class UActionGameplayAbility;
/**
 * 
 */
UCLASS()
class ACTION_API UDataAsset_StartUpDataBase : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual void
	GiveToAbilitySystemComponent(UActionAbilitySystemComponent* InActionASCToGive, int32 ApplyLevel = 1);

protected:
	/// @brief 激活时需要授予的游戏能力类数组
	/// @details 存储当此数据资产被应用时，需要授予给角色的游戏能力类列表
	/// @note TSubclassOf 用于存储类引用，可以存储任何继承自 UActionGameplayAbility 的类
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UActionGameplayAbility>> ActivateOnGivenAbilities;

	/// @brief 需要重新激活的游戏能力类列表
	/// @details 存储的是 UActionGameplayAbility 类或其子类的类引用，用于在特定时机重新激活这些能力
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UActionGameplayAbility>> ReActivateAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UGameplayEffect>> StartUpEffects;

	void GrantAbilities(const TArray<TSubclassOf<UActionGameplayAbility>>& InAbilitiesToGive,
	                    UActionAbilitySystemComponent* InActionASCToGive, int32 ApplyLevel = 1);
};
