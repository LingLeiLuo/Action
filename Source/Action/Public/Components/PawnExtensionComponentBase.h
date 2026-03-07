// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PawnExtensionComponentBase.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTION_API UPawnExtensionComponentBase : public UActorComponent
{
	GENERATED_BODY()

protected:
	/// @brief 获取拥有此组件的 Pawn 指针
	/// @tparam T Pawn 类型，必须派生自 APawn
	/// @return 转换为指定类型的 Pawn 指针
	/// @throws 如果转换失败，会触发断言错误
	template <class T>
	T* GetOwningPawn() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, APawn>::Value, "T 必须派生自 APawn");
		return CastChecked<T>(GetOwner());
	}

	/**
 * @brief 获取拥有此组件的 Pawn
 * @return 拥有此组件的 Pawn 指针，如果不存在则返回 nullptr
 */
	APawn* GetOwningPawn() const
	{
		return GetOwningPawn<APawn>();
	}


	/**
	* @brief 获取拥有此组件的控制器
    * 
    * @tparam T 控制器类型，必须派生自 AController
    * @return T* 指向拥有控制器的指针，如果不存在则返回 nullptr
    * 
    * @throws static_assert 如果 T 不是 AController 的派生类，编译时会报错
    * 
    * @note 此函数内部通过 GetOwningPawn 获取拥有者 Pawn，再从 Pawn 获取控制器
    */
	template <class T>
	T* GetOwningController() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, AController>::Value, "T 必须派生自 AController");
		return GetOwningPawn<APawn>()->GetController<T>();
	}
};
