// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ActionAttributeSet.h"
#include "GameplayEffectExtension.h"

#include "ActionDebugHelper.h"

UActionAttributeSet::UActionAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitCurrentEnergy(1.f);
	InitMaxEnergy(1.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);
}

void UActionAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	// 当某个GameEffect修改属性时，其修改的是生命值，则进行操作
	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);
	}

	if (Data.EvaluatedData.Attribute == GetCurrentEnergyAttribute())
	{
		const float NewCurrentEnergy = FMath::Clamp(GetCurrentEnergy(), 0.f, GetMaxEnergy());
		SetCurrentEnergy(NewCurrentEnergy);
	}

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHealth();
		const float DamageDone = GetDamageTaken();

		const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageDone, 0.f, GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);

		const FString DebugString = FString::Printf(
			TEXT("Old Health: %f, Damage Done: %f, New Health: %f"),
			OldHealth,
			DamageDone,
			NewCurrentHealth
		);

		Debug::Print(DebugString, FColor::Green);

		//TODO: Notify the UI

		//TODO: Death
		if (NewCurrentHealth == 0.f)
		{
		}
	}
}
