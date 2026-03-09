// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/ActionAbilitySystemComponent.h"

UActionAbilitySystemComponent* UActionFunctionLibrary::NativeGetActionActionAbilitySystemComponentFromActor(AActor* InActor)
{
	check(InActor);

	return CastChecked<UActionAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void UActionFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag InGameplayTag)
{
	check(InActor);
	check(InGameplayTag.IsValid());

	UActionAbilitySystemComponent* AbilitySystemComponent = NativeGetActionActionAbilitySystemComponentFromActor(InActor);
	if (!AbilitySystemComponent->HasMatchingGameplayTag(InGameplayTag))
	{
		AbilitySystemComponent->AddLooseGameplayTag(InGameplayTag);
	}
}

void UActionFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag InGameplayTag)
{
	check(InActor);
	check(InGameplayTag.IsValid());

	UActionAbilitySystemComponent* AbilitySystemComponent = NativeGetActionActionAbilitySystemComponentFromActor(InActor);

	if (AbilitySystemComponent->HasMatchingGameplayTag(InGameplayTag))
	{
		AbilitySystemComponent->RemoveLooseGameplayTag(InGameplayTag);
	}
}

bool UActionFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag InGameplayTag)
{
	UActionAbilitySystemComponent* AbilitySystemComponent = NativeGetActionActionAbilitySystemComponentFromActor(InActor);
	
	return AbilitySystemComponent->HasMatchingGameplayTag(InGameplayTag);
}

void UActionFunctionLibrary::K2_DoesActorHaveTag(AActor* InActor, FGameplayTag InGameplayTag,
	EActionConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor, InGameplayTag) ? EActionConfirmType::Yes : EActionConfirmType::No;
}

