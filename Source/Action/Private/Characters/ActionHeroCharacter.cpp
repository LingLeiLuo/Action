// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ActionHeroCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "ActionDebugHelper.h"

/**
 * @brief 构造函数，初始化 ActionHeroCharacter 的默认属性和组件
 * 
 * 设置角色胶囊体大小、控制器旋转行为、摄像机臂和跟随摄像机等核心组件，
 * 并配置角色移动参数（如朝向移动方向旋转、最大行走速度等）
 */
AActionHeroCharacter::AActionHeroCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(40.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
}

void AActionHeroCharacter::BeginPlay()
{
	Super::BeginPlay();

	Debug::Print(TEXT("BeginPlay"));
}
