// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ActionWidgetBase.h"

#include "Interfaces/PawnUIInterface.h"

void UActionWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(GetOwningPlayerPawn()))
	{
		if (UHeroUIComponent* HeroUIComponent = PawnUIInterface->GetHeroUIComponent())
		{
			BP_OnOwningHeroUIComponentInitialized(HeroUIComponent);
		}
	}
	
	
}
