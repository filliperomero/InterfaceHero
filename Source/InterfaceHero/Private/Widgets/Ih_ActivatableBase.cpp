// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Ih_ActivatableBase.h"
#include "Player/Ih_PlayerController.h"

AIh_PlayerController* UIh_ActivatableBase::GetOwningIhPlayerController()
{
	if (!CachedOwningIhPlayerController.IsValid())
	{
		CachedOwningIhPlayerController = GetOwningPlayer<AIh_PlayerController>();
	}

	return CachedOwningIhPlayerController.IsValid() ? CachedOwningIhPlayerController.Get() : nullptr;
}
