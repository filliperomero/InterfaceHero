// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Ih_ActivatableBase.generated.h"

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class INTERFACEHERO_API UIh_ActivatableBase : public UCommonActivatableWidget
{
	GENERATED_BODY()
};
