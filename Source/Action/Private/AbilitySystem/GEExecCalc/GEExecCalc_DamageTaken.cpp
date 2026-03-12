// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GEExecCalc/GEExecCalc_DamageTaken.h"

#include "ActionDebugHelper.h"
#include "ActionGameplayTags.h"
#include "AbilitySystem/ActionAttributeSet.h"

struct FActionDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

	FActionDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UActionAttributeSet, AttackPower, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UActionAttributeSet, DefensePower, Target, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UActionAttributeSet, DamageTaken, Target, false)
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

void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                     FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();
	// EffectSpec.GetContext().GetSourceObject();
	// EffectSpec.GetContext().GetAbility();
	// EffectSpec.GetContext().GetInstigator();
	// EffectSpec.GetContext().GetEffectCauser();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttackPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetActionDamageCapture().AttackPowerDef,
	                                                           EvaluateParameters, SourceAttackPower);
	Debug::Print(TEXT("SourceAttackPower"), SourceAttackPower);

	float BaseDamage = 0.f;
	int32 UsedLightAttackComboCount = 0;
	int32 UsedHeavyAttackComboCount = 0;

	for (const TPair<FGameplayTag, float>& TagMagnitudePair : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitudePair.Key.MatchesTagExact(ActionGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitudePair.Value;
			Debug::Print(TEXT("BaseDamage"), BaseDamage);
		}

		if (TagMagnitudePair.Key.MatchesTagExact(ActionGameplayTags::Player_SetByCaller_AttackType_Light))
		{
			UsedLightAttackComboCount = TagMagnitudePair.Value;
			Debug::Print(TEXT("UsedLightAttackComboCount"), UsedLightAttackComboCount);
		}

		if (TagMagnitudePair.Key.MatchesTagExact(ActionGameplayTags::Player_SetByCaller_AttackType_Heavy))
		{
			UsedHeavyAttackComboCount = TagMagnitudePair.Value;
			Debug::Print(TEXT("UsedHeavyAttackComboCount"), UsedHeavyAttackComboCount);
		}
	}

	float TargetDefensePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetActionDamageCapture().DefensePowerDef,
	                                                           EvaluateParameters, TargetDefensePower);
	Debug::Print(TEXT("TargetDefensePower"), TargetDefensePower);

	if (UsedLightAttackComboCount != 0)
	{
		const float DamageIncreasePercentLight = (UsedLightAttackComboCount - 1) * 0.05 + 1.f;

		BaseDamage *= DamageIncreasePercentLight;

		Debug::Print(TEXT("ScaledBaseDamageLight"), BaseDamage);
	}

	if (UsedHeavyAttackComboCount != 0)
	{
		const float DamageIncreasePercentHeavy = (UsedHeavyAttackComboCount - 1) * 0.15 + 1.f;

		BaseDamage *= DamageIncreasePercentHeavy;

		Debug::Print(TEXT("ScaledBaseDamageHeavy"), BaseDamage);
	}

	const float FinalDamage = BaseDamage * SourceAttackPower / TargetDefensePower;
	Debug::Print(TEXT("FinalDamage"), FinalDamage);

	if (FinalDamage > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				GetActionDamageCapture().DamageTakenProperty,
				EGameplayModOp::Override,
				FinalDamage
			)
		);
	}
}
