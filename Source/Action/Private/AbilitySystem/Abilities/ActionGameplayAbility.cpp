// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ActionGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/Combat/PawnCombatComponent.h"

/**
 * @brief 当能力被赋予给角色时调用
 * 
 * 此方法处理能力被赋予时的初始化逻辑。如果能力的激活模式设置为 OnGiven，
 * 则会在赋予后立即尝试激活该能力。
 * 
 * @param ActorInfo 拥有此能力的角色信息指针
 * @param Spec 描述此能力规格的 Gameplay Ability Spec
 * 
 * @note 需要确保 ActorInfo 有效且 Spec 处于非激活状态才会尝试激活能力
 * @see EActionGameplayAbilityActivationMode::OnGiven
 */
void UActionGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (GameplayAbilityActivationMode == EActionGameplayAbilityActivationMode::OnGiven)
	{
		if (ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

/**
 * @brief 结束游戏玩法能力
 * 
 * 调用父类的结束能力方法，并根据激活模式处理能力清理。
 * 如果激活模式为 OnGiven，则从能力系统组件中清除该能力。
 * 
 * @param Handle 能力规范句柄，用于标识能力实例
 * @param ActorInfo 拥有该能力的角色信息指针
 * @param ActivationInfo 能力激活信息，包含激活相关的上下文数据
 * @param bReplicateEndAbility 是否向网络复制结束能力事件
 * @param bWasCancelled 能力是否被取消，true 表示被取消，false 表示正常结束
 */
void UActionGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo,
                                        const FGameplayAbilityActivationInfo ActivationInfo,
                                        bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (GameplayAbilityActivationMode == EActionGameplayAbilityActivationMode::OnGiven)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

UPawnCombatComponent* UActionGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}

UActionAbilitySystemComponent* UActionGameplayAbility::GetActionAbilitySystemComponentFromActorInfo() const
{
	return Cast<UActionAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

FActiveGameplayEffectHandle UActionGameplayAbility::NativeApplyEffectSpecHandleToTarget(AActor* TargetActor,
	const FGameplayEffectSpecHandle& InEffectSpecHandle)
{
	UAbilitySystemComponent* TargetTAbilitySystemComponent =
		UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	check(TargetTAbilitySystemComponent && InEffectSpecHandle.IsValid());

	return GetActionAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(
		*InEffectSpecHandle.Data,
		TargetTAbilitySystemComponent
	);
}

FActiveGameplayEffectHandle UActionGameplayAbility::K2_ApplyEffectSpecHandleToTarget(AActor* TargetActor,
	const FGameplayEffectSpecHandle& InEffectSpecHandle, EActionSuccessType& OutSuccessType)
{
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = NativeApplyEffectSpecHandleToTarget(
		TargetActor, InEffectSpecHandle);

	OutSuccessType = ActiveGameplayEffectHandle.WasSuccessfullyApplied()
		                 ? EActionSuccessType::Success
		                 : EActionSuccessType::Failed;

	return ActiveGameplayEffectHandle;
}
