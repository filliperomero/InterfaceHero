// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Ih_ActivatableBase.generated.h"

class AIh_PlayerController;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class INTERFACEHERO_API UIh_ActivatableBase : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintPure)
	AIh_PlayerController* GetOwningIhPlayerController();

private:
	TWeakObjectPtr<AIh_PlayerController> CachedOwningIhPlayerController;
};
