// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/ActionCharacterAnimInstance.h"

#include "Characters/ActionBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"


/**
 * @brief 初始化动画实例
 * 
 * 在动画实例初始化时调用，用于获取并缓存角色引用和角色移动组件引用
 * 
 * @see TryGetPawnOwner
 * @see AActionBaseCharacter::GetCharacterMovement
 */
void UActionCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<AActionBaseCharacter>(TryGetPawnOwner());

	if (OwningCharacter)
	{
		OwingCharacterMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

/**
 * @brief 线程安全地更新动画实例数据
 * 
 * 每帧调用此函数以更新动画相关的变量，包括角色移动速度和加速度状态。
 * 该函数是线程安全的，可在动画线程中调用。
 * 
 * @param DeltaSeconds 距离上一帧的时间增量（秒）
 * 
 * @note 如果 OwingCharacter 或 OwingCharacterMovementComponent 为空，则直接返回
 * @see UActionCharacterAnimInstance::GroundSpeed
 * @see UActionCharacterAnimInstance::bHasAcceleration
 */
void UActionCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwingCharacterMovementComponent)
	{
		return;
	}

	GroundSpeed = OwningCharacter->GetVelocity().Size2D();

	bHasAcceleration = OwingCharacterMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;

	LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(OwningCharacter->GetVelocity(), OwningCharacter->GetActorRotation()); 
}
