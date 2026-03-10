// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/ActionAbilitySystemComponent.h"
#include "Characters/ActionBaseCharacter.h"

UActionAbilitySystemComponent* UActionFunctionLibrary::NativeGetActionActionAbilitySystemComponentFromActor(
	AActor* InActor)
{
	check(InActor);

	return CastChecked<UActionAbilitySystemComponent>(
		UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void UActionFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag InGameplayTagToAdd)
{
	check(InActor);
	check(InGameplayTagToAdd.IsValid());

	UActionAbilitySystemComponent* AbilitySystemComponent =
		NativeGetActionActionAbilitySystemComponentFromActor(InActor);
	if (!AbilitySystemComponent->HasMatchingGameplayTag(InGameplayTagToAdd))
	{
		AbilitySystemComponent->AddLooseGameplayTag(InGameplayTagToAdd);
	}
}

void UActionFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag InGameplayTagToRemove)
{
	check(InActor);
	check(InGameplayTagToRemove.IsValid());

	UActionAbilitySystemComponent* AbilitySystemComponent =
		NativeGetActionActionAbilitySystemComponentFromActor(InActor);

	if (AbilitySystemComponent->HasMatchingGameplayTag(InGameplayTagToRemove))
	{
		AbilitySystemComponent->RemoveLooseGameplayTag(InGameplayTagToRemove);
	}
}

bool UActionFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag InGameplayTagToCheck)
{
	UActionAbilitySystemComponent* AbilitySystemComponent =
		NativeGetActionActionAbilitySystemComponentFromActor(InActor);

	return AbilitySystemComponent->HasMatchingGameplayTag(InGameplayTagToCheck);
}

void UActionFunctionLibrary::K2_DoesActorHaveTag(AActor* InActor, FGameplayTag InGameplayTagToCheck,
                                                 EActionConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor, InGameplayTagToCheck)
		                 ? EActionConfirmType::Yes
		                 : EActionConfirmType::No;
}

UPawnCombatComponent* UActionFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	check(InActor);

	if (IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
	{
		return PawnCombatInterface->GetPawnCombatComponent();
	}

	return nullptr;
}

UPawnCombatComponent* UActionFunctionLibrary::K2_GetPawnCombatComponentFromActor(AActor* InActor,
	EActionValidType& OutValidType)
{
	UPawnCombatComponent* CombatComponent = NativeGetPawnCombatComponentFromActor(InActor);

	OutValidType = CombatComponent ? EActionValidType::Valid : EActionValidType::Invalid;

	return CombatComponent;
}
