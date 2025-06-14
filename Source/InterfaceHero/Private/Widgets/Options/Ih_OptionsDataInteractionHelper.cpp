// Copyright Fillipe Romero. All Rights Reserved.

#include "Widgets/Options/Ih_OptionsDataInteractionHelper.h"
#include "Settings/Ih_GameUserSettings.h"

FIh_OptionsDataInteractionHelper::FIh_OptionsDataInteractionHelper(const FString& InSetterOrGetterFuncPath)
	: CachedDynamicFunctionPath(InSetterOrGetterFuncPath)
{
	CachedWeakGameUserSettings = UIh_GameUserSettings::Get();
}

FString FIh_OptionsDataInteractionHelper::GetValueAsString() const
{
	FString OutStringValue;
	PropertyPathHelpers::GetPropertyValueAsString(CachedWeakGameUserSettings.Get(), CachedDynamicFunctionPath, OutStringValue);

	return OutStringValue;
}

void FIh_OptionsDataInteractionHelper::SetValueFromString(const FString& InStringValue)
{
	PropertyPathHelpers::SetPropertyValueFromString(CachedWeakGameUserSettings.Get(), CachedDynamicFunctionPath, InStringValue);
}
