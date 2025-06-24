// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Options/DataObjects/Ih_ListDataObject_StringBool.h"

void UIh_ListDataObject_StringBool::OverrideTrueDisplayText(const FText& InNewTrueDisplayText)
{
	if (!AvailableOptionsStringArray.Contains(TrueString))
	{
		AddDynamicOption(TrueString, InNewTrueDisplayText);
	}
}

void UIh_ListDataObject_StringBool::OverrideFalseDisplayText(const FText& InNewFalseDisplayText)
{
	if (!AvailableOptionsStringArray.Contains(FalseString))
	{
		AddDynamicOption(FalseString, InNewFalseDisplayText);
	}
}

void UIh_ListDataObject_StringBool::SetTrueAsDefaultValue()
{
	SetDefaultValueFromString(TrueString);
}

void UIh_ListDataObject_StringBool::SetFalseAsDefaultValue()
{
	SetDefaultValueFromString(FalseString);
}

void UIh_ListDataObject_StringBool::OnDataObjectInitialized()
{
	TryInitBoolValues();

	Super::OnDataObjectInitialized();
}

void UIh_ListDataObject_StringBool::TryInitBoolValues()
{
	if (!AvailableOptionsStringArray.Contains(TrueString))
	{
		AddDynamicOption(TrueString, FText::FromString(TEXT("ON")));
	}

	if (!AvailableOptionsStringArray.Contains(FalseString))
	{
		AddDynamicOption(FalseString, FText::FromString(TEXT("OFF")));
	}
}
