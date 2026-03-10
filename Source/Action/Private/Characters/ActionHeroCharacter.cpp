// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ActionHeroCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "Components/Input/ActionInputComponent.h"

#include "ActionGameplayTags.h"
#include "AbilitySystem/ActionAbilitySystemComponent.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"

#include "ActionDebugHelper.h"
#include "Components/Combat/HeroCombatComponent.h"


/**
 * @brief 构造函数，初始化主角角色的默认属性和组件
 * 
 * 设置角色胶囊体大小、控制器旋转行为、摄像机弹簧臂和跟随摄像机，
 * 以及角色移动相关的参数，包括朝向移动、旋转速率、最大行走速度和制动减速度
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
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	HeroCombatComponent = CreateDefaultSubobject<UHeroCombatComponent>(TEXT("HeroCombatComponent"));
}

UPawnCombatComponent* AActionHeroCharacter::GetPawnCombatComponent() const
{
	return HeroCombatComponent;
}

void AActionHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// if (ActionAbilitySystemComponent && ActionAttributeSet)
	// {
	// 	const FString ASCText = FString::Printf(
	// 		TEXT("Owner Actor: %s, Avatar Actor: %s"), *ActionAbilitySystemComponent->GetOwnerActor()->GetActorLabel(),
	// 		*ActionAbilitySystemComponent->GetAvatarActor()->GetActorLabel());
	//
	// 	Debug::Print(TEXT("Ability System Component 合法.") + ASCText, FColor::Green);
	// 	Debug::Print(TEXT("Attribute Set 合法.") + ASCText, FColor::Green);
	// }

	if (!CharacterStartUpData.IsNull())
	{
		if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.LoadSynchronous())
		{
			LoadedData->GiveToAbilitySystemComponent(ActionAbilitySystemComponent);
		}
	}
}

/**
 * @brief 设置玩家输入组件，绑定输入映射和输入动作
 * 
 * 此函数初始化增强输入系统，添加输入映射上下文，并将输入动作绑定到对应的处理函数。
 * 使用输入配置数据资产中的配置来设置移动等输入绑定。
 * 
 * @param PlayerInputComponent 玩家输入组件指针，用于绑定输入动作
 * 
 * @throws checkf 如果 InputConfigDataAsset 为空则抛出异常
 * @throws check 如果 EnhancedInputSubsystem 为空则抛出异常
 */
void AActionHeroCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("InputConfigDataAsset is null"));

	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<
		UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(EnhancedInputSubsystem);

	EnhancedInputSubsystem->AddMappingContext(InputConfigDataAsset->InputMappingContext, 0);

	UActionInputComponent* ActionInputComponent = Cast<UActionInputComponent>(PlayerInputComponent);

	ActionInputComponent->BindNativeInputAction(InputConfigDataAsset, ActionGameplayTags::InputTag_Move,
	                                            ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	ActionInputComponent->BindNativeInputAction(InputConfigDataAsset, ActionGameplayTags::InputTag_Look,
	                                            ETriggerEvent::Triggered, this, &ThisClass::Input_Look);

	ActionInputComponent->BindNativeInputAction(InputConfigDataAsset, ActionGameplayTags::InputTag_Look,
	                                            ETriggerEvent::Triggered, this, &ThisClass::Input_Look);
	ActionInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &ThisClass::Input_AbilityInputPressed,
	                                             &ThisClass::Input_AbilityInputReleased);
}

void AActionHeroCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Debug::Print(TEXT("BeginPlay"));
}

/**
 * @brief 处理角色移动输入
 * 
 * 根据输入的移动向量值，计算相对于控制器朝向的前进和右移方向，
 * 并调用 AddMovementInput 应用移动输入。
 * 
 * @param InInputActionValue 输入动作值，包含二维移动向量（X为左右，Y为前后）
 */
void AActionHeroCharacter::Input_Move(const FInputActionValue& InInputActionValue)
{
	const FVector2D MoveVector = InInputActionValue.Get<FVector2D>();
	const FRotator MoveRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

	if (MoveVector.Y != 0.f)
	{
		const FVector ForwardVector = MoveRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardVector, MoveVector.Y);
	}

	if (MoveVector.X != 0.f)
	{
		const FVector RightVector = MoveRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightVector, MoveVector.X);
	}
}

void AActionHeroCharacter::Input_Look(const FInputActionValue& InInputActionValue)
{
	const FVector2D LookVector = InInputActionValue.Get<FVector2D>();

	if (LookVector.X != 0.f)
	{
		AddControllerYawInput(LookVector.X);
	}

	if (LookVector.Y != 0.f)
	{
		AddControllerPitchInput(LookVector.Y);
	}
}

void AActionHeroCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	ActionAbilitySystemComponent->OnAbilityInputPressed(InInputTag);
}

void AActionHeroCharacter::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	ActionAbilitySystemComponent->OnAbilityInputReleased(InInputTag);
}
