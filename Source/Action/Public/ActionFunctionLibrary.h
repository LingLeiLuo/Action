// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ActionFunctionLibrary.generated.h"

struct FGameplayTag;
class UActionAbilitySystemComponent;

UENUM()
enum class EActionConfirmType : uint8
{
	Yes,
	No
};

UCLASS()
class ACTION_API UActionFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static UActionAbilitySystemComponent* NativeGetActionActionAbilitySystemComponentFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "Action|FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag InGameplayTag);

	UFUNCTION(BlueprintCallable, Category = "Action|FunctionLibrary")
	static void RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag InGameplayTag);

	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag InGameplayTag);

	UFUNCTION(BlueprintCallable, Category = "Action|FunctionLibrary", meta=(DisplayName="Does Actor Have Tag", ExpandEnumAsExecs="OutConfirmType"))
	static void K2_DoesActorHaveTag(AActor* InActor, FGameplayTag InGameplayTag, EActionConfirmType& OutConfirmType);
};
