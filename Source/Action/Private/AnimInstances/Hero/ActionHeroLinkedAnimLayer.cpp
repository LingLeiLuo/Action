// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Hero/ActionHeroLinkedAnimLayer.h"

#include "AnimInstances/Hero/ActionHeroAnimInstance.h"

UActionHeroAnimInstance* UActionHeroLinkedAnimLayer::GetHeroAnimInstance() const
{
	return Cast<UActionHeroAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
