// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Ih_ListEntry_Base.h"
#include "Ih_ListEntry_String.generated.h"

class UIh_ListDataObject_String;
class UIh_CommonRotator;
class UIh_CommonButtonBase;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class INTERFACEHERO_API UIh_ListEntry_String : public UIh_ListEntry_Base
{
	GENERATED_BODY()

protected:
	virtual void OnOwningListDataObjectSet(UIh_ListDataObject_Base* InOwningListDataObject) override;

private:
	/** Bound Widgets */
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess="true"))
	TObjectPtr<UIh_CommonButtonBase> CommonButton_PreviousOption;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess="true"))
	TObjectPtr<UIh_CommonRotator> CommonRotator_AvailableOptions;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess="true"))
	TObjectPtr<UIh_CommonButtonBase> CommonButton_NextOption;
	/** Bound Widgets */

	UPROPERTY(Transient)
	TObjectPtr<UIh_ListDataObject_String> CachedOwningStringDataObject;
};
