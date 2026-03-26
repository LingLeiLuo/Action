// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/EnemyCombatComponent.h"

#include "ActionDebugHelper.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* InHitActor)
{
	if (InHitActor)
	{
		Debug::Print("Solis ");
	}
	
}
