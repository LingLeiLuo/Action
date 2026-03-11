// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/PawnExtensionComponentBase.h"


#include "ActionDefines/ActionEnumDefines.h"
#include "PawnCombatComponent.generated.h"

class AActionWeaponBase;

/**
 * 
 */
UCLASS()
class ACTION_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Action|Combat")
	void RegisterSpawnWeapon(FGameplayTag InWeaponTagToRegister, AActionWeaponBase* InWeaponToRegister,
	                         bool bRegisterAsEquippedWeapon = false);

	UFUNCTION(BlueprintCallable, Category = "Action|Combat")
	AActionWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTag) const;

	UPROPERTY(BlueprintReadWrite, Category="Action|Combat")
	FGameplayTag CurrentEquippedWeaponTag;

	UFUNCTION(BlueprintCallable, Category="Action|Combat")
	AActionWeaponBase* GetCharacterCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category="Action|Combat")
	void ToggleWeaponCollision(bool bEnable, EToggleDmgType ToggleDmgType = EToggleDmgType::CurrentEquippedWeapon);

	virtual void OnHitTargetActor(AActor* InHitActor);
	virtual void OnPulledFromTargetActor(AActor* InInteractedActor);

protected:
	TArray<AActor*> OverlappedActors;

private:
	TMap<FGameplayTag, AActionWeaponBase*> CharacterCarriedWeaponMap;
};
