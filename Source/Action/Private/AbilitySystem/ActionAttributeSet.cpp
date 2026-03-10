// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ActionAttributeSet.h"

UActionAttributeSet::UActionAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitCurrentEnergy(1.f);
	InitMaxEnergy(1.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);
}
