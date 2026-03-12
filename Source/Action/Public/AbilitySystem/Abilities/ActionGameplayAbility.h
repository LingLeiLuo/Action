// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystem/ActionAbilitySystemComponent.h"
#include "ActionDefines/ActionEnumDefines.h"
#include "ActionGameplayAbility.generated.h"

class UPawnCombatComponent;

UENUM(BlueprintType)
enum class EActionGameplayAbilityActivationMode : uint8
{
	OnTriggered,
	OnGiven
};

UCLASS()
class ACTION_API UActionGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	// UGameplayAbility 接口 Begin
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                        const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
	                        bool bWasCancelled) override;
	// UGameplayAbility 接口 End

	UPROPERTY(EditDefaultsOnly, Category = "ActionAbility")
	EActionGameplayAbilityActivationMode GameplayAbilityActivationMode =
		EActionGameplayAbilityActivationMode::OnTriggered;

	UFUNCTION(BlueprintPure, Category = "Action|Ability")
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category = "Action|Ability")
	UActionAbilitySystemComponent* GetActionAbilitySystemComponentFromActorInfo() const;

	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* TargetActor,
	                                                                const FGameplayEffectSpecHandle&
	                                                                InEffectSpecHandle);

	UFUNCTION(BlueprintCallable, Category = "Action|Ability",
		meta=(DisplayName = "Apply Effect Spec Handle To Target", ExpandEnumAsExecs="OutSuccessType"))
	FActiveGameplayEffectHandle K2_ApplyEffectSpecHandleToTarget(AActor* TargetActor,
	                                                             const FGameplayEffectSpecHandle&
	                                                             InEffectSpecHandle,
	                                                             EActionSuccessType& OutSuccessType);
};
