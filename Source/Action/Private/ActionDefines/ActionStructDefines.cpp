// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionDefines/ActionStructDefines.h"

#include "AbilitySystem/Abilities/ActionGameplayAbility.h"

bool FActionHeroAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}
