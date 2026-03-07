// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "ActionInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class ACTION_API UActionInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	/**
	 * @brief 绑定原生输入动作到指定的回调函数
	 * 
	 * 根据输入配置数据资产和输入标签查找对应的输入动作，并将其绑定到指定的回调函数。
	 * 
	 * @tparam UserObject 上下文对象的类型
	 * @tparam CallbackFunc 回调函数的类型
	 * @param InInputConfig 输入配置数据资产，用于查找输入动作
	 * @param InInputTag 用于标识输入动作的游戏标签
	 * @param TriggerEvent 触发事件类型（如按下、释放等）
	 * @param ContextObject 拥有回调函数的上下文对象指针
	 * @param InCallbackFunc 输入动作触发时调用的回调函数
	 * 
	 * @note 如果 InInputConfig 为空，会触发断言失败
	 * @note 只有在配置中找到对应的输入动作时才会执行绑定
	 */
	template <class UserObject, typename CallbackFunc>
	inline void BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag,
	                                  ETriggerEvent TriggerEvent, UserObject* ContextObject,
	                                  CallbackFunc InCallbackFunc);

	template <class UserObject, typename CallbackFunc>
	inline void BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig, UserObject* ContextObject,
	                                   CallbackFunc InputPressFunc, CallbackFunc InputReleaseFunc);
};

template <class UserObject, typename CallbackFunc>
inline void UActionInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig,
                                                         const FGameplayTag& InInputTag,
                                                         ETriggerEvent TriggerEvent, UserObject* ContextObject,
                                                         CallbackFunc InCallbackFunc)
{
	checkf(InInputConfig, TEXT("Input Config Data Asset is null"));

	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundAction, TriggerEvent, ContextObject, InCallbackFunc);
	}
}

template <class UserObject, typename CallbackFunc>
inline void UActionInputComponent::BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig,
                                                          UserObject* ContextObject,
                                                          CallbackFunc InputPressFunc, CallbackFunc InputReleaseFunc)
{
	checkf(InInputConfig, TEXT("Input Config Data Asset is null"));

	for (const FActionInputActionConfig& InputActionConfig : InInputConfig->AbilityInputActions)
	{
		if (!InputActionConfig.IsValid())
		{
			continue;
		}

		BindAction(InputActionConfig.InputAction, ETriggerEvent::Started, ContextObject, InputPressFunc,
		           InputActionConfig.InputTag);
		BindAction(InputActionConfig.InputAction, ETriggerEvent::Completed, ContextObject, InputReleaseFunc,
		           InputActionConfig.InputTag);
	}
}
