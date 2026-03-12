// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "ActionAttributeSet.generated.h"

/**
 * @brief 定义游戏属性访问器的宏
 * @details 该宏为指定的类和属性名称生成一组标准的属性访问方法，包括：
 *          - 属性获取器（Property Getter）
 *          - 属性值获取器（Value Getter）
 *          - 属性值设置器（Value Setter）
 *          - 属性值初始化器（Value Initializer）
 * @param ClassName 类名，用于生成属性访问器
 * @param PropertyName 属性名称，用于生成对应的访问方法
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class ACTION_API UActionAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UActionAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UActionAttributeSet, CurrentHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UActionAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Energy")
	FGameplayAttributeData CurrentEnergy;
	ATTRIBUTE_ACCESSORS(UActionAttributeSet, CurrentEnergy)

	UPROPERTY(BlueprintReadOnly, Category = "Energy")
	FGameplayAttributeData MaxEnergy;
	ATTRIBUTE_ACCESSORS(UActionAttributeSet, MaxEnergy)

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UActionAttributeSet, AttackPower)

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(UActionAttributeSet, DefensePower)

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData DamageTaken;
	ATTRIBUTE_ACCESSORS(UActionAttributeSet, DamageTaken)
};
