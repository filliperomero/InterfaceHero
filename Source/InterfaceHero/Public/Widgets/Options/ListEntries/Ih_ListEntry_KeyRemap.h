// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Ih_ListEntry_Base.h"
#include "Ih_ListEntry_KeyRemap.generated.h"

class UIh_CommonButtonBase;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class INTERFACEHERO_API UIh_ListEntry_KeyRemap : public UIh_ListEntry_Base
{
	GENERATED_BODY()

private:
	/** Bound Widgets */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	TObjectPtr<UIh_CommonButtonBase> CommonButton_RemapKey;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	TObjectPtr<UIh_CommonButtonBase> CommonButton_ResetKeyBinding;
	/** Bound Widgets */
};
