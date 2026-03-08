// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/ActionBaseAnimInstance.h"
#include "ActionHeroLinkedAnimLayer.generated.h"

class UActionHeroAnimInstance;
/**
 * 
 */
UCLASS()
class ACTION_API UActionHeroLinkedAnimLayer : public UActionBaseAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta=(BlueprintThreadSafe))
	UActionHeroAnimInstance* GetHeroAnimInstance() const;
};
