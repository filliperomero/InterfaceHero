// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Ih_ListEntry_Base.h"
#include "Ih_ListEntry_Scalar.generated.h"

class UAnalogSlider;
class UCommonNumericTextBlock;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class INTERFACEHERO_API UIh_ListEntry_Scalar : public UIh_ListEntry_Base
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	virtual void OnOwningListDataObjectSet(UIh_ListDataObject_Base* InOwningListDataObject) override;
	virtual void OnOwningListDataObjectModified(UIh_ListDataObject_Base* OwningModifiedData, EIh_OptionsListDataModifyReason ModifyReason) override;

private:
	/** Bound Widgets */
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess="true"))
	TObjectPtr<UCommonNumericTextBlock> CommonNumeric_SettingValue;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess="true"))
	TObjectPtr<UAnalogSlider> AnalogSlider_SettingSlider;
	/** Bound Widgets */
};
