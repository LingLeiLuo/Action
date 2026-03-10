// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ActionDefines/ActionEnumDefines.h"
#include "ActionFunctionLibrary.generated.h"

class UPawnCombatComponent;
struct FGameplayTag;
class UActionAbilitySystemComponent;

UCLASS()
class ACTION_API UActionFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static UActionAbilitySystemComponent* NativeGetActionActionAbilitySystemComponentFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "Action|FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag InGameplayTagToAdd);

	UFUNCTION(BlueprintCallable, Category = "Action|FunctionLibrary")
	static void RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag InGameplayTagToRemove);

	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag InGameplayTagToCheck);

	UFUNCTION(BlueprintCallable, Category = "Action|FunctionLibrary",
		meta=(DisplayName="Does Actor Have Tag", ExpandEnumAsExecs="OutConfirmType"))
	static void K2_DoesActorHaveTag(AActor* InActor, FGameplayTag InGameplayTagToCheck,
	                                EActionConfirmType& OutConfirmType);

	static UPawnCombatComponent* NativeGetPawnCombatComponentFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "Action|FunctionLibrary",
		meta=(DisplayName="Get Pawn Combat Component From Actor", ExpandEnumAsExecs="OutValidType"))
	static UPawnCombatComponent*
	K2_GetPawnCombatComponentFromActor(AActor* InActor, EActionValidType& OutValidType);
};
