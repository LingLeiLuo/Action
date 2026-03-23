// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/ActionHeroController.h"

AActionHeroController::AActionHeroController()
{
	TeamId = FGenericTeamId(0);
}

FGenericTeamId AActionHeroController::GetGenericTeamId() const
{
	return TeamId;
}
