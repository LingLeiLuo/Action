// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/DataAsset_HeroStartUpData.h"

#include "AbilitySystem/Abilities/ActionGameplayAbility.h"

void UDataAsset_HeroStartUpData::GiveToAbilitySystemComponent(UActionAbilitySystemComponent* InActionASCToGive,
                                                              int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InActionASCToGive, ApplyLevel);

	for (const FActionHeroAbilitySet& AbilitySet : HeroStartUpAbilitySets)
	{
		if (!AbilitySet.IsValid())
		{
			continue;
		}

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InActionASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

		InActionASCToGive->GiveAbility(AbilitySpec);
	}
}
