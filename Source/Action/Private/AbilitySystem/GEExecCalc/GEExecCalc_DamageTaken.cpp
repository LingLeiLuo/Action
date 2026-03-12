// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GEExecCalc/GEExecCalc_DamageTaken.h"

#include "AbilitySystem/ActionAttributeSet.h"

struct FActionDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)

	FActionDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UActionAttributeSet, AttackPower, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UActionAttributeSet, DefensePower, Target, false)
	}
};

static const FActionDamageCapture& GetActionDamageCapture()
{
	static FActionDamageCapture ActionDamageCapture;
	return ActionDamageCapture;
}

UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{
	// 慢一点的方式

	// FProperty* AttackPowerDefProperty = FindFieldChecked<FProperty>(
	// 	UActionAttributeSet::StaticClass(),
	// 	GET_MEMBER_NAME_CHECKED(UActionAttributeSet, AttackPower)
	// );
	//
	// FGameplayEffectAttributeCaptureDefinition AttackPowerCaptureDefinition(
	// 	AttackPowerDefProperty,
	// 	EGameplayEffectAttributeCaptureSource::Source,
	// 	false
	// );
	//
	// RelevantAttributesToCapture.Add(AttackPowerCaptureDefinition);

	RelevantAttributesToCapture.Add(GetActionDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetActionDamageCapture().DefensePowerDef);
}
