// Copyright Fillipe Romero. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonNumericTextBlock.h"
#include "Ih_ListDataObject_Value.h"
#include "Ih_ListDataObject_Scalar.generated.h"


UCLASS()
class INTERFACEHERO_API UIh_ListDataObject_Scalar : public UIh_ListDataObject_Value
{
	GENERATED_BODY()

public:
	static FCommonNumberFormattingOptions NoDecimal();
	static FCommonNumberFormattingOptions WithDecimal(int32 NumFracDigit);

	float GetCurrentValue() const;
	void SetCurrentValueFromSlider(float InNewValue);
	
	virtual bool CanResetBackToDefaultValue() const override;
	virtual bool TryResetBackToDefaultValue() override;

protected:
	virtual void OnEditDependencyDataModified(UIh_ListDataObject_Base* ModifiedDependencyData, EIh_OptionsListDataModifyReason ModifyReason = EIh_OptionsListDataModifyReason::DirectlyModified) override;

private:
	float StringToFloat(const FString& InString) const;
	
	TRange<float> DisplayValueRange { TRange<float>(0.f, 1.f) };
	TRange<float> OutputValueRange { TRange<float>(0.f, 1.f) };
	float SliderStepSize { 0.1f };
	ECommonNumericType DisplayNumericType { ECommonNumericType::Number };
	FCommonNumberFormattingOptions NumberFormattingOptions;

public:
	LIST_DATA_ACCESSOR(TRange<float>, DisplayValueRange);
	LIST_DATA_ACCESSOR(TRange<float>, OutputValueRange);
	LIST_DATA_ACCESSOR(float, SliderStepSize);
	LIST_DATA_ACCESSOR(ECommonNumericType, DisplayNumericType);
	LIST_DATA_ACCESSOR(FCommonNumberFormattingOptions, NumberFormattingOptions);
};
