// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Options/DataObjects/Ih_ListDataObject_Scalar.h"
#include "Widgets/Options/Ih_OptionsDataInteractionHelper.h"

FCommonNumberFormattingOptions UIh_ListDataObject_Scalar::NoDecimal()
{
	FCommonNumberFormattingOptions Options;
	Options.MaximumFractionalDigits = 0;
	
	return Options;
}

FCommonNumberFormattingOptions UIh_ListDataObject_Scalar::WithDecimal(int32 NumFracDigit)
{
	FCommonNumberFormattingOptions Options;
	Options.MaximumFractionalDigits = NumFracDigit;
	
	return Options;
}

float UIh_ListDataObject_Scalar::GetCurrentValue() const
{
	if (DataDynamicGetter)
	{
		return FMath::GetMappedRangeValueClamped(OutputValueRange, DisplayValueRange, StringToFloat(DataDynamicGetter->GetValueAsString()));
	}

	return 0.0f;
}

float UIh_ListDataObject_Scalar::StringToFloat(const FString& InString) const
{
	float OutConvertedValue = 0.f;
	
	LexFromString(OutConvertedValue, *InString);

	return OutConvertedValue;
}
